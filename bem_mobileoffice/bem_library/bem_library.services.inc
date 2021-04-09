<?php
/**
 * @File Enable Library Serivices
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info This module contains functions to enable services to retrive content of blocks
 * @vertion dev 1.0.0.0
 */

/**
 * Implement hook_services_resources().
 * @see module Services
 * Funtion to declare service
 */
function bem_library_services_resources(){
  $resource = array(
    'library' => array(
      'operations' => array(
        'index' => array(
          'help'             => 'Listado y filtrado de Documentos de Bibliotecas',
          'callback'         => 'bem_library_servresults',
          'access callback'  => 'bem_library_permission',
          'access arguments' => array('library serv'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name'        => 'filters',
              'type'        => 'array',
              'description' => '',
              'source'      => array('param' => 'filters'),
              'optional'    => TRUE,
              'default'     => [],
            ),
          ),
        ), // end index
      ), // end operations
    ), // end latest
  );

  return $resource;
}

/**
 * Funtion to validate params of service
 * @see bem_library_service_content
 * @param array ($filters)
 * @return boolean ($validate)
 */
function bem_library_servicevalidate($filters) {
  $success = TRUE;

  // Validate empty params
  if ( $filters === NULL ) {
    return $success;
  } // endif

  // Validate all params numeric
  foreach ($filters[0] as $param => $value) {

    if ( !is_numeric($value) ) {
      $success = FALSE;
      return $success;
    } // endif
  }// endforeach

  return $success;
}

/**
 * Callback to return filters to service (countries)
 * @see library_public_filters
 * @return theme array ($content)
 */
function bem_library_pubfilters() {
  $content = [];

  // Load contry info by user session
  $ip      = $_SERVER['REMOTE_ADDR'];
  $country = bem_common_ip_user();
  $acron   = ( isset($country['country_code']) && !empty($country['country_code']) ) ? $country['country_code'] : '--';

  // Load Vocab
  $vocab = taxonomy_vocabulary_machine_name_load('biblioteca_pa_ses_');
  $vid   = $vocab->vid;

  // Query to retrive terms
  $qry = db_select('taxonomy_term_data', 'ttd');
  $qry->leftJoin('field_data_field_bbp_codigo_iso', 'acron', 'acron.entity_id = ttd.tid');
  $qry->condition('ttd.vid', $vid, '=');
  $qry->fields('ttd', ['tid', 'name']);
  $qry->fields('acron', ['field_bbp_codigo_iso_value']);
  $qry->orderBy('weight', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    $flag = $i = 0;
    foreach ($results as $result) {
      $content[$result->tid]['class'] = '';
      $content[$result->tid]['name'] = $result->name;
      if ($result->field_bbp_codigo_iso_value == $acron ) {
        $content[$result->tid]['class'] = 'selected';
        $flag = 1;
      }// endif
      if ($i == 0) {
        $tid = $result->tid;
      }// endif

      ++$i;
    } // endforeach
    if ($flag == 0) {
      $content[$tid]['class'] = 'selected';
    } // endif

  } // endif

  return $content;
}

/**
 * Callback to return contents of service
 * @see bem_library_servresults,
 * @param array ($filters) params on service request
 * @return array ($titles) data to content of call
 */
function bem_library_servtitles($filters, $type){
  $titles = [];

  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_field_bbn_categoria', 'fc', 'fc.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_tipo_categoria', 'ftc', 'ftc.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_posicion', 'pos', 'pos.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_pais', 'fp', 'fp.entity_id = n.nid');
  $qry->condition('n.type', 'bibliotecas_new');
  // Filter by type (Pub/Priv)
  $qry->condition('ftc.field_bbn_tipo_categoria_value', $type);
  // filter by contry
  if ( isset($filters[0]['country']) && !empty($filters[0]['country']) ) {
    $qry->condition('fp.field_bbn_pais_tid', $filters[0]['country']);
  } // endif
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('fc', ['field_bbn_categoria_value'])
      ->fields('pos', ['field_bbn_posicion_value']);
  $qry->orderBy('pos.field_bbn_posicion_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {
      $content[] = [
        'nid'  => $result->nid,
        'name' => $result->field_bbn_categoria_value,
      ];
    }// endforeach

    $titles = array_chunk($content, 5, TRUE);
  } // endif

  return $titles;
}

/**
 * Callback to return contents of service
 * @see bem_library_services_resources, bem_library_block_view
 * @param array ($filters) params on service request
 * @return object ($response) data to content of call
 */
function bem_library_servresults($filters = NULL) {
  $response = new stdClass();
  $content = [];
  global $user;

  if (isset($filters[0]) && is_string($filters[0])) {
    // Decode filters on request
    $filters = json_decode($filters[0], true);
  }

  // validate params on service request
  $validate = bem_library_servicevalidate($filters);

  if ($validate === TRUE) {
    $pub_content  = bem_library_getdocs($filters, '0');
    $priv_content = bem_library_getdocs($filters, '1');

    // response with content
    //$response->filters    = json_encode($filters);
    $response->success    = TRUE;
    $response->message    = "success";
    $response->mobtabspub = $pub_content['mobtabs'];
    $response->tabspub    = $pub_content['tabs'];
    $response->datapub    = $pub_content['content'];
    $response->mobtabsprv = $priv_content['mobtabs'];
    $response->tabspriv   = $priv_content['tabs'];
    $response->datapriv   = $priv_content['content'];

  } // endif

  return $response;
}

/**
 * Callback to return contents of service
 * @see bem_library_servresults
 * @param array ($filters) params on service request
 * @return object ($response) data to content of call
 */

function bem_library_getdocs($filters, $type) {
  $content = $response = $titles = $mobtabs = [];
  global $user;
  $type = (int) $type;

  $titles   = bem_library_servtitles($filters, $type);

  foreach ($titles as $rows) {
    foreach ($rows as $value) {
      $mobtabs[] = [
        'nid'  => $value['nid'],
        'name' => $value['name'],
      ];
    } // endoforeach
  } // endoforeach


  $category = ( isset($filters[0]['category']) && $filters[0]['category'] != 0  ) ? $filters[0]['category'] : $titles[0][0]['nid'];

  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_field_bbn_categoria', 'fc', 'fc.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_tipo_categoria', 'ftc', 'ftc.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_documentos', 'fd', 'fd.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_posicion', 'pos', 'pos.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bbn_pais', 'fp', 'fp.entity_id = n.nid');
  $qry->condition('n.type', 'bibliotecas_new');
  // Filter by type (Pub/Priv)
  $qry->condition('ftc.field_bbn_tipo_categoria_value', $type);

  // filter by country
  if ( isset($filters[0]['country']) && !empty($filters[0]['country']) ) {
    $country = (int) $filters[0]['country'];
    $qry->condition('fp.field_bbn_pais_tid', $country);
  } // endif
  // Filter by NID (category)
  $qry->condition('n.nid', $category);
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('fc', ['field_bbn_categoria_value'])
      ->fields('ftc', ['field_bbn_tipo_categoria_value'])
      ->fields('fd', ['field_bbn_documentos_field_bbn_ano_1_url',
                      'field_bbn_documentos_field_bbn_ano_1_title',
                      'field_bbn_documentos_field_bbn_ano_2_url',
                      'field_bbn_documentos_field_bbn_ano_2_title',
                      'field_bbn_documentos_field_bbn_nombre_archivo_value',
                      'field_bbn_documentos_field_bbn_subcategoria_value',
                      'field_bbn_documentos_id',
                      'delta'])
      ->fields('pos', ['field_bbn_posicion_value'])
      ->fields('fp', ['field_bbn_pais_tid']);
  $qry->orderBy('fd.delta', 'ASC');
  $qry->orderBy('fd.delta', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    $i = 1;
    foreach ($results as $result) {
      $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['nid']   = $result->nid;
      $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['delta'] = $i;
      $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['type'] = 'pub';

      /* Introducción diferente de docmentos 24-08-20 */
      if ( $result->field_bbn_documentos_field_bbn_subcategoria_value == "Material para canales digitales") {

        $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['intro'] = "Te pueden interesar los siguientes documentos o materiales digitales";

      } else {
        $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['intro'] = "Te pueden interesar los siguientes documentos";
      } // endif

      if ($user->uid == 0 && $type == 1) {
        $theme_path = $base_url.'/'.drupal_get_path('theme', 'bptheme');
        $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['type'] = 'priv';
        $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['docs'][$result->delta] = [
          'name'  => !empty($result->field_bbn_documentos_field_bbn_nombre_archivo_value) ? $result->field_bbn_documentos_field_bbn_nombre_archivo_value : '--',
          'a_one' => $theme_path.'/img/icons/guia/lock.svg',
          'f_one' => $base_url.'/bem-login?redirectProtectedNodeId='.$result->nid,
        ];
      }
      else {
        $content[$result->field_bbn_documentos_field_bbn_subcategoria_value]['docs'][$result->delta] = [
          'name'  => !empty($result->field_bbn_documentos_field_bbn_nombre_archivo_value) ? $result->field_bbn_documentos_field_bbn_nombre_archivo_value : '--',
          'a_one' => !empty($result->field_bbn_documentos_field_bbn_ano_1_title) ? $result->field_bbn_documentos_field_bbn_ano_1_title : '--',
          'f_one' => !empty($result->field_bbn_documentos_field_bbn_ano_1_url) ? $result->field_bbn_documentos_field_bbn_ano_1_url : ' ',
          'a_two' => !empty($result->field_bbn_documentos_field_bbn_ano_2_title) ? $result->field_bbn_documentos_field_bbn_ano_2_title : '--',
          'f_two' => !empty($result->field_bbn_documentos_field_bbn_ano_2_url) ? $result->field_bbn_documentos_field_bbn_ano_2_url : ' ',
        ];
      }
      ++$i;
    } // endforeach

    // Order docs by rows
    foreach ($content as $key => $value) {
      $docs = array_chunk($value['docs'], 3, TRUE);
      $content[$key]['docs'] = $docs;
    }// endforeach
  } // endif

  $response['tabs']    = $titles;
  $response['content'] = $content;
  $response['mobtabs'] = $mobtabs;

  return $response;
}
