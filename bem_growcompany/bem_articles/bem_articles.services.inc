<?php
/**
 * @File Enable Articles Serivices
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Crece tu Empresa
 * @info This module contains functions to enable services to retrive content of blocks
 * @vertion dev 1.0.0.0
 */

/**
 * Implement hook_services_resources().
 * @see module Services
 * Funtion to declare service
 */
function bem_articles_services_resources(){
  $resource = array(
    'articles' => array(
      'operations' => array(
        'index' => array(
          'help'             => 'Listado y filtrado de Artículos',
          'callback'         => 'bem_articles_service_content',
          'access callback'  => 'bem_articles_permission',
          'access arguments' => array('articles serv'),
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
            array(
              'name'        => 'page',
              'type'        => 'int',
              'description' => '',
              'source'      => array('param' => 'page'),
              'optional'    => TRUE,
              'default'     => 1,
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
 * @see bem_articles_service_content
 * @param array ($filters)
 * @return boolean ($validate)
 */
function bem_articles_servicevalidate($filters) {
  $success = TRUE;

  if ( $filters === NULL ) {
    return $success;
  } // endif

  foreach ($filters[0] as $param => $filter) {
    if ($param != "search") {
      foreach ($filter as $value) {
        if ( !is_numeric($value) ) {
          $success = FALSE;
          return $success;
        } // endif
      }// endforeach
    }//endif
  }// endforeach

  return $success;
}

/**
 * Callback to return contents of service
 * @see bem_articles_services_resources, bem_articles_block_view
 * @param array ($filters) params on service request
 * @return object ($response) data to content of call
 */
function bem_articles_service_content($filters = NULL) {
  $response = new stdClass();
  $content  = [];

  $filters = json_decode($filters[0], true);

  // validate params on service request
  $validate = bem_articles_servicevalidate($filters);

  if ($validate === TRUE) {
    // Get machine names to filter content
    $category = bem_articles_getmachiname($filters);

    // Search
    $search  = (string) $filters[0]['search'];
    $results = _bem_articles_results($filters, $category, $search);

    if ( !empty($results)) {
      global $base_url;
      $total = 0;
      $offset = (isset($filters[0]['offset'])) ? $filters[0]['offset'] : 0;
      $i = 0;

      foreach ($results as $art) {
          $path = drupal_get_path_alias('node/' . $art->nid) . '#segment=' . $offset;
          // General Structure
          $content[$i] = [
              'title'         => $art->title,
              'desc'          => truncate_utf8($art->body_summary, 150, FALSE, TRUE),
              'type'          => !empty($art->name) ? $art->name : t('Artículo'),
              'c_type'        => $art->type,
              'path'          => $base_url . '/' . $path,
              'path_print'    => $base_url . '/' . drupal_get_path_alias('node/' . $art->nid) . '#print',
              'facebook_path' => 'https://www.facebook.com/share.php?u=' .$base_url.'/'.$path . '&title=' . $art->title,
              'linkedin_path' => 'https://www.linkedin.com/sharing/share-offsite/?url=' . $base_url.'/'. $path . '&title=' . $art->title,
              'twitter_path'  => 'https://twitter.com/share?url=' .$base_url.'/'. $path . '&text=' . $art->title,
              'print_path'    => $base_url . '/print/' . $art->nid,
              'fecha'         => $art->field_fecha_articulos_value,
              'frame'         => $i,
              'promote'       => $art->promote,
          ];
        // Structure by content type
        switch ($art->type) {
          case 'documentos_de_inter_s_':
            $content[$i]['img'] = bem_common_getimg($art->field_imagen_destacada_fid);
            $content[$i]['pdf'] = bem_common_getimg($art->field_pdf_descargable_fid);
            break;
          case 'articulo_conocimiento_industria':
            $content[$i]['img'] = bem_common_getimg($art->field_imagen_articulo_destacado_fid);
            $content[$i]['pdf'] = bem_common_getimg($art->field_descarga_pdf_ci_fid);
            break;
          case 'capacitaciones':
            $content[$i]['img'] = bem_common_getimg($art->field_imagen_destacada_cp_fid);
            $content[$i]['pdf'] = bem_common_getimg($art->field_pdf_descargable_cp_fid);
            break;
          case 'tutoriales':
            $content[$i]['img'] = bem_common_getimg($art->field_imagen_tutorial_fid);
            break;
          case 'webinars':
            $content[$i]['img'] = bem_common_getimg($art->field_uimg_desk_fid);
            $content[$i]['pdf'] = bem_common_getimg($art->field_pdf_descargable_fid);
            break;
          case 'tip_de_ventas':
            $content[$i]['img'] = isset($art->field_imagen_destacada_cp_fid) ?bem_common_getimg($art->field_imagen_destacada_cp_fid) : '';
            $content[$i]['pdf'] = isset($art->field_pdf_descargable_cp_fid) ?
             bem_common_getimg($art->field_pdf_descargable_cp_fid) : '';
             break;
          default:
            $content[$i]['img'] = isset($art->field_imagen_destacada_cp_fid) ?bem_common_getimg($art->field_imagen_destacada_cp_fid) : '';
            break;
        }
        ++$total;
        $i++;
      }// endforeach
      // Make response object

      $response->filters      = json_encode($filters);
      $response->success      = TRUE;
      $response->message      = "success";
      $response->totalResults = $total;
      $response->data         = $content;
      $response->total        = _bem_articles_results($filters, $category, $search, FALSE);
      $response->pages        = ceil(($response->total / 9));

    } else {
        $response->success = TRUE;
        $response->message = "error";
        $response->total   = 0;
        $response->data    = [];
        $response->pages   = 0;
    }// endif

  } //endif

  return $response;
}

/**
 * @param array $filters
 * @param bool $range
 * @return array
 */
function _bem_articles_results($filters, $category, $search, $range = TRUE) {
    $results = [];
    $results2 = [];
    $qry2 = new stdClass();
    try {
        $qry = db_select('node', 'n');
        // Globals
        $qry->leftJoin('field_data_field_fecha_articulos', 'ffa', 'ffa.entity_id = n.nid');
        $qry->leftJoin('field_data_field_type_articles', 'tp', 'tp.entity_id = n.nid');
        $qry->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
        $qry->leftJoin('taxonomy_term_data', 'ttd', 'ttd.tid = tp.field_type_articles_tid');
        // Documentos de interes
        $qry->leftJoin('field_data_field_imagen_destacada', 'diimg', 'diimg.entity_id = n.nid');
        $qry->leftJoin('field_data_field_pdf_descargable', 'dipdf', 'dipdf.entity_id = n.nid');
        // Conocimiento de la Industria
        $qry->leftJoin('field_data_field_imagen_articulo_destacado', 'ciimg', 'ciimg.entity_id = n.nid');
        $qry->leftJoin('field_data_field_descarga_pdf_ci', 'cipdf', 'cipdf.entity_id = n.nid');
        // Capacitaciones
        $qry->leftJoin('field_data_field_imagen_destacada_cp', 'cpimg', 'cpimg.entity_id = n.nid');
        $qry->leftJoin('field_data_field_pdf_descargable_cp', 'cppdf', 'cppdf.entity_id = n.nid');
        // Tutoriales
        $qry->leftJoin('field_data_field_imagen_tutorial', 'tuimg', 'tuimg.entity_id = n.nid');
        // Webinars
        $qry->leftJoin('field_data_field_uimg_desk', 'weimg', 'weimg.entity_id = n.nid');

        $qry->leftJoin('field_data_field_pdf_descargable', 'wepdf', 'wepdf.entity_id = n.nid');

        $qry->leftJoin('field_data_field_content_filter_arts', 'cfarts', 'cfarts.entity_id = n.nid');
        $qry->condition('status', 1, '=');

        /* CONDITION TO FILTERS */
        $qry->condition('ffa.entity_type', 'node', '=');

        // Condition to select categorories
        if ( !empty($category) ) {
            $db_cat = db_or();
            foreach ($category as $machinename) {
                $db_cat->condition('n.type', $machinename, '=');
            } // endforeach
            $qry->condition($db_cat);

            foreach ($category as $key => $value) {
                $db_cat->condition('cfarts.field_content_filter_arts_tid', $key, '=');
            } // endforeach
            $qry->condition($db_cat);

        } // endif

        // Condition to select sub-categorories
        if ( isset($filters[0]['subcategory']) && !empty($filters[0]['subcategory']) && count($filters[0]['subcategory']) ) {
            $qry->leftJoin('field_data_field_categoria_documento_intere', 'disub', 'disub.entity_id = n.nid');
            $db_subcat = db_or();
            foreach ($filters[0]['subcategory'] as $subcategory) {
                $db_subcat->condition('disub.field_categoria_documento_intere_tid', $subcategory, '=');
            }// endforeach
            $qry->condition($db_subcat);
        }// endif

        // Condition to select type
        if ( isset($filters[0]['type']) && !empty($filters[0]['type']) && count($filters[0]['type'])) {
            $qry->leftJoin('field_data_field_type_articles', 'ftype', 'ftype.entity_id = n.nid');
            $db_type = db_or();
            foreach ($filters[0]['type'] as $ftype) {
                $db_type->condition('ftype.field_type_articles_tid', $ftype, '=');
            }// endforeach
            $qry->condition($db_type);
        }// endif

        // Condition to search
        if ( !empty($search) ) {
            $db_or = db_or();
            $terms = explode(" ", $search);
            foreach ($terms as $term) {
                $db_or->condition('n.title', '%' . db_like($term) . '%', 'LIKE');
            } // end foreache

            $db_or->condition('body.body_value', '%' . db_like($search) . '%', 'LIKE');

            $qry->condition($db_or);
        } // endif

        /* END CONDITION TO FILTERS */
        // Fields
        $qry->fields('n', ['nid', 'title', 'type','promote'])
            ->fields('tp', ['field_type_articles_tid'])
            ->fields('body', ['body_summary'])
            ->fields('ttd', ['tid', 'name'])
            ->fields('diimg', ['field_imagen_destacada_fid'])
            ->fields('dipdf', ['field_pdf_descargable_fid'])
            ->fields('ciimg', ['field_imagen_articulo_destacado_fid'])
            ->fields('cipdf', ['field_descarga_pdf_ci_fid'])
            ->fields('cpimg', ['field_imagen_destacada_cp_fid'])
            ->fields('cppdf', ['field_pdf_descargable_cp_fid'])
            ->fields('tuimg', ['field_imagen_tutorial_fid'])
            ->fields('weimg', ['field_uimg_desk_fid'])
            ->fields('wepdf', ['field_pdf_descargable_fid'])
            ->fields('ffa', ['field_fecha_articulos_value']);

        $qry2 = clone $qry;
        /*
          02-09-20 Se cambia orderBy para hacer una consulta dinámica usando como 1er parametro
          el status de PROMOTE
         */
        $qry->orderBy('n.promote', 'DESC')
            ->orderBy('ffa.field_fecha_articulos_value','DESC');

        /* CONDITION TO FILTERS */
        /* 02-09-20 Se omiten condiciones para obtener todos los artículos */
        //$qry->condition('n.promote', 0, '=');
        //$qry2->condition('n.promote', 1, '=');

        if (!$range) {
            $results = $qry2->execute()->rowCount();
            $results2 = $qry->execute()->rowCount();

            return ($results + $results2);
        } // end if

        /* 02-09-20 Se ajusta valor iniciar a 0 para recuperar todos los items desde el principio */
        $offset = ( isset($filters[0]['offset']) && $filters[0]['offset'] > 1 ) ? $filters[0]['offset'] : 0;
        $qry->range($offset, variable_get("page_limit", ""));

        $results2 = $qry->execute()->fetchAll();


        /* 02-09-20 Se omite IF por descarte de valor inicial de offset */
        /*
        if ($offset == 0 ) {
          $results = $qry2->execute()->fetchAll();
        }
        else{
          $results = [];
        }*/

        $results = array_merge($results, $results2);

    } catch (Exception $e) {

    } // end try - catch


    return $results;
}


/**
 * Function to return machine name of content types on filters
 * @see bem_articles_service_content
 * @param array ($filters) array with TIDS since filters
 * @return array ($categories) machine names to filter content
 */
function bem_articles_getmachiname($filters){
  $categories = [];
  // Load Vocab
  $vocab = taxonomy_vocabulary_machine_name_load('content_articles');
  $vid   = $vocab->vid;
  // Query to get terms
  $qry = db_select('taxonomy_term_data', 'ttd');
  $qry->condition('ttd.vid', $vid, '=');
  if ( isset($filters[0]['category']) && count($filters[0]['category']) ) {
    $db_or = db_or();
    foreach ($filters[0]['category'] as $tid) {
      $db_or->condition('ttd.tid', $tid, '=');
    }// endforeach
    $qry->condition($db_or);
  } // endif
  $qry->fields('ttd', ['tid', 'name', 'description']);
  $qry->orderBy('weight', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {
      $categories[$result->tid] = $result->description;
    } // endforeach
  } // endif

  return $categories;
}
