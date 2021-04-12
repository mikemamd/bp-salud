<?php
/**
 * @File Redesign "Planes de Viaje"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info Functions to return content to blocks
 * @vertion dev 1.0.0.0
 */

/**
 * Return content to block [bem_travel_intro]
 * @return theme array ($content)
 */
function bem_travel_plans_getintro() {
  // Get tmp variables
  $content = [
    'title' => variable_get('travel_intro_title',''),
    'intro' => variable_get('travel_intro_intro',''),
    'body'  => variable_get('travel_intro_desc', ''),
    'img'   => bem_common_getimg(variable_get('travel_intro_img', '')),
  ];

  return theme('bem_travel_intro', array('content' => $content));
}

/**
 * Return content to block [bem_travel_intro]
 * @return theme array ($content)
 */
function bem_travel_plans_getservices() {
  $content = [];

  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bta_posicion', 'ord', 'ord.entity_id = n.nid');
  $qry->condition('n.type', 'bp_travel_acordeon');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('ord', ['field_bta_posicion_value']);
  $qry->orderBy('ord.field_bta_posicion_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  // Each array to structure content
  foreach ($results as $node) {
    // Make array with node content
    $content[$node->nid] = [
      'title' => $node->title,
      'desc'  => $node->body_value,
    ];

  } // endforeach

  return theme('bem_travel_services', array('content' => $content));
}

/**
 * Return content to block [bem_travel_plans]
 * @return theme array ($content)
 */
function bem_travel_plans_getplans() {
  $content = $info = [];
  global $base_url;

  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder', 'ord', 'ord.entity_id = n.nid');
  $qry->leftJoin('field_data_field_btp_material', 'doc', 'doc.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uimg_desk', 'img', 'img.entity_id = n.nid');
  $qry->condition('n.type', 'travelplans_plans');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('doc', ['field_btp_material_field_btp_nombre_documento_value', 'field_btp_material_field_btp_url_url'])
      ->fields('img', ['field_uimg_desk_fid'])
      ->fields('ord', ['field_uorder_value']);
  $qry->orderBy('ord.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  if ( !empty($results) ) {
    // Each array to structure content
    foreach ($results as $node) {
      // Make array with node content
      $content[$node->nid] = [
        'title' => $node->title,
        'desc'  => $node->body_value,
        'img'   => bem_common_getimg($node->field_uimg_desk_fid),
      ];

      // Order to materials
      $materials[$node->nid][] = [
        'file' => $node->field_btp_material_field_btp_url_url,
        'name' => $node->field_btp_material_field_btp_nombre_documento_value,
        'down' => $base_url .'/'. drupal_get_path('theme', 'bptheme') . '/img/icons/hoja.svg',
      ];

      // Merge arrays to content and files
      foreach ($materials as $nid => $item) {
        $content[$nid]['materials'] = $item;
      } // endforeach
    } // endforeach

  }// endif

  $info = [
    'title' => variable_get('travel_plans_title',''),
    'desc'  => variable_get('travel_plans_desc',''),
  ];

  return theme('bem_travel_plans', array('content' => $content, 'info' => $info));
}

/**
 * Return content to block [bem_travel_quote]
 * @return theme array ($content)
 */
function bem_travel_plans_getquote(){
  global $base_url;
  $content = [];

  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder', 'ord', 'ord.entity_id = n.nid');
  $qry->leftJoin('field_data_field_link', 'link', 'link.entity_id = n.nid');
  $qry->leftJoin('field_data_field_travel_new_tab', 'nt', 'nt.entity_id = n.nid');
  $qry->condition('n.type', 'travelplans_quote');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('link', ['field_link_url', 'field_link_title'])
      ->fields('ord', ['field_uorder_value'])
      ->fields('nt', ['field_travel_new_tab_value']);
  $qry->orderBy('ord.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  if ( !empty($results) ) {
    foreach ($results as $item) {
      $content[] = [
        'title'  => $item->title,
        'desc'   => $item->body_value,
        'path'   => $item->field_link_url,
        'path_t' => $item->field_link_title,
        'target' => $item->field_travel_new_tab_value,
      ];
    }// endforeach
  } // endif

  return theme('bem_travel_quote', array('content' => $content));
}

/**
 * Return content to block [bem_travel_materials]
 * @return theme array ($content)
 */
function bem_travel_plans_getmaterials(){
  global $base_url;
  $content = $info = [];

  // Retrive content
  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_field_btp_material', 'file', 'file.entity_id = n.nid');
  $qry->leftJoin('field_data_field_btp_posicion', 'ord', 'ord.entity_id = n.nid');
  $qry->condition('n.type', 'bp_travel_pdfs');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('file', ['field_btp_material_field_btp_nombre_documento_value', 'field_btp_material_field_btp_url_url'])
      ->fields('ord', ['field_btp_posicion_value']);
  $qry->orderBy('ord.field_btp_posicion_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  if ( !empty($results) ) {
    foreach ($results as $file) {
      $content[$file->nid] = [ 'section' => $file->title ];

      $materials[$file->nid][] = [
        'file' => $file->field_btp_material_field_btp_url_url,
        'name' => $file->field_btp_material_field_btp_nombre_documento_value,
        'down' => $base_url .'/'. drupal_get_path('theme', 'bptheme') . '/img/icons/hoja.svg',
      ];

      // Merge arrays to content and files
      foreach ($materials as $nid => $item) {
        $content[$nid]['materials'] = $item;
      } // endforeach

    }// endforeach
  }// endif

  $info = [
    'title' => variable_get('travel_files_title',''),
    'desc'  => variable_get('travel_files_desc',''),
    'icon'  => bem_common_getimg(variable_get('travel_files_svg','')),
  ];

  return theme('bem_travel_materials', array('content' => $content, 'info' => $info));
}
