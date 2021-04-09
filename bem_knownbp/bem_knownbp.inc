<?php
/**
 * @File Redesign Home
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD
 * @info Functions to return content to blocks
 * @vertion dev 1.0.0.0
 */

/*
 * Return content to block [know_who_history]
 * @return theme array ($content)
 */
function bem_knownbp_whohistory(){
  global $base_url;
  $content = [];

  $flag = ['date_one','date_two','date_three','date_four','date_five','date_six','date_seven','date_eight','date_nine', ];

  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_body', 'fb', 'fb.entity_id = n.nid');
  $query->leftJoin('field_data_field_cuerpo', 'fc', 'fc.entity_id = n.nid');
  $query->leftJoin('field_data_field_uorder', 'ffo', 'ffo.entity_id = n.nid');
  $query->leftJoin('field_data_field_icon_svg', 'svg', 'svg.entity_id = n.nid');
  $query->condition('n.type', 'knowbp_qeb_history');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title'])
        ->fields('fb', ['field_body_value'])
        ->fields('fc', ['field_cuerpo_value'])
        ->fields('ffo', ['field_uorder_value'])
        ->fields('svg', ['field_icon_svg_fid']);
  $query->orderBy('ffo.field_uorder_value', 'ASC');
  $results = $query->execute()->fetchAll();

  if ( !empty($results) ) {
    foreach ($results as $key => $result) {
      $content[] = [
        'nid'    => $result->nid,
        'title'  => $result->title,
        'colone' => $result->field_body_value,
        'coltwo' => $result->field_cuerpo_value,
        'icon'   => !empty ($result->field_icon_svg_fid) ? bem_common_getimg($result->field_icon_svg_fid) : '',
        'order'  => $result->field_uorder_value,
        'flag'   => $flag[$key],
        'class'  => ($key == 0) ? 'active' : '',
      ];
    }//endfor
  }//endif

  $block = block_load('bem_knownbp', 'know_who_history');

  return theme('know_who_history', array('content' => $content, 'block_title' => $block->title));
}

/*
 * Return content to block [know_who_strt]
 * @return theme array ($content)
 */
function bem_knownbp_whostrt(){
  global $base_url;
  $content = [];

  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_body', 'fb', 'fb.entity_id = n.nid');
  $query->leftJoin('field_data_field_uorder', 'ffo', 'ffo.entity_id = n.nid');
  $query->leftJoin('field_data_field_icon_svg', 'svg', 'svg.entity_id = n.nid');
  $query->condition('n.type', 'knowbp_qeb_cards');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title'])
        ->fields('fb', ['field_body_value'])
        ->fields('ffo', ['field_uorder_value'])
        ->fields('svg', ['field_icon_svg_fid']);
  $query->orderBy('ffo.field_uorder_value', 'ASC');
  $results = $query->execute()->fetchAll();

  if ( !empty($results) ) {
    foreach ($results as $result) {
      $content['cards'][] = [
        'nid'   => $result->nid,
        'title' => $result->title,
        'desc'  => $result->field_body_value,
        'icon'  => !empty($result->field_icon_svg_fid) ? bem_common_getimg($result->field_icon_svg_fid) : '',
        'order' => $result->field_uorder_value,
      ];
    }//endfor
  }//endif

  $content['header'] = [
    'title' => variable_get('whoisbp_strtitle',''),
    'body'  => variable_get('whoisbp_strbody',''),
  ];

  return theme('know_who_strt', array('content' => $content));
}

/*
 * Return content to block [know_who_vision]
 * @return theme array ($content)
 */
function bem_knownbp_whovision(){
  $content = [];
  // Search origin content
  $query = db_select('node', 'n');
  $query->condition('n.type', 'knowbp_qeb_vision');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title']);
  $query->orderBy('n.changed', 'ASC');
  $result = $query->execute()->fetchAll();

  // Load node content
  $node = node_load($result[0]->nid);
  // Array with the final info
  $content['content'] = [
    'title' => $node->title,
    'desc'  => $node->body['und'][0]['value'],
    'img'   => bem_common_getimg($node->field_uimg_desk['und'][0]['fid']),
  ];
  foreach ($node->field_bem_collect['und'] as $key => $collect) {
    $content['points'][] = [
      'class'   => ($key == 1) ? 'my-4' : '',
      'content' => $collect['field_bemcollect_title']['und'][0]['value'],
      'svg'     => !empty($collect['field_icon_svg']['und'][0]['fid']) ? bem_common_getimg($collect['field_icon_svg']['und'][0]['fid']) : '',
    ];
  } // endforeach

  return theme('know_who_vision', array('content' => $content));
}

/*
 * Return content to block [know_who_prup]
 * @return theme array ($content)
 */
function bem_knownbp_whoprup(){
  $content = [];
  // Load Vocab
  $vocab   = taxonomy_vocabulary_machine_name_load('knowbp_qeb_purpose');
  $vid     = $vocab->vid;
  // Query to get terms
  $query = db_select('taxonomy_term_data', 'tx');
  $query->leftJoin('field_data_field_icon_svg', 'fsvg', 'fsvg.entity_id = tx.tid');
  $query->condition('tx.vid', $vid, '=');
  $query->fields('tx', ['tid', 'name', 'description'])
        ->fields('fsvg', ['field_icon_svg_fid']);
  $query->orderBy('weight', 'ASC');
  $results = $query->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {
      $content['valors'][] = [
        'tid'  => $result->tid,
        'name' => $result->name,
        'icon' => !empty($result->field_icon_svg_fid) ? bem_common_getimg($result->field_icon_svg_fid) : '',
      ];
    }
  }

  //Block info
  $content['content'] = [
    'title' => variable_get('whoisbp_pruptitle', ''),
    'desc'  => variable_get('whoisbp_prupbody', ''),
    'url'   => !empty(variable_get('whoisbp_img', '')) ? bem_common_getimg(variable_get('whoisbp_img', '')) : '',
  ];

  return theme('know_who_prup', array('content' => $content));
}

/*
 * Return content to block [know_why_intro]
 * @return theme array ($content)
 */
function bem_knownbp_whyintro(){
  $content = [];
  // Search origin content
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_body', 'fb', 'fb.entity_id = n.nid');
  $query->leftJoin('field_data_field_uorder', 'fu', 'fu.entity_id = n.nid');
  $query->leftJoin('field_data_field_icon_svg', 'svg', 'svg.entity_id = n.nid');
  $query->condition('n.type', 'knowbp_pqb_intro');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title'])
        ->fields('fb', ['field_body_value'])
        ->fields('fu', ['field_uorder_value'])
        ->fields('svg', ['field_icon_svg_fid']);
  $query->orderBy('fu.field_uorder_value', 'ASC');
  $results = $query->execute()->fetchAll();

  if ( !empty($results) ) {
    foreach ($results as $result) {
      $content[$result->field_uorder_value] = [
        'order' => $result->field_uorder_value,
        'title' => $result->title,
        'body'  => $result->field_body_value,
        'svg'   => bem_common_getimg($result->field_icon_svg_fid),
      ];
    } // endforeach
  } //endif

  return theme('know_why_intro', array('content' => $content));
}

/*
 * Return content to block [know_why_sales]
 * @return theme array ($content)
 */
function bem_knownbp_whysales(){
  $content = [];
  // Search NID
  $query = db_select('node', 'n');
  $query->condition('n.type', 'knowbp_pb_sales');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid']);
  $query->orderBy('n.changed', 'ASC');
  $results = $query->execute()->fetchAll();
  // Load Node
  if ( !empty($results) ) {
    $node = node_load($results[0]->nid);

    // Array with node content to template
    $content = [
      'title'    => $node->title,
      'subtitle' => $node->field_usubtitle['und'][0]['value'],
      'saleinfo' => $node->field_sales_info['und'][0]['value'],
    ];
    // Foreach to collect content to sales
    foreach ($node->field_sales_collect['und'] as $key => $item) {
      $content['infoicons'][] = [
        'icon'   => bem_common_getimg($item['field_icon_svg']['und'][0]['fid']),
        'number' => $item['field_sales_numeric']['und'][0]['value'],
        'bold'   => (isset($item['field_sales_bold']['und'][0])) ? $item['field_sales_bold']['und'][0]['value'] : '',
        'normal' => $item['field_sales_normal']['und'][0]['value'],
        'class'  => ($key == 1) ? 'clientes' : ' ',
      ];
    } // endforeach
    // Foreach to collect content to medics info
    foreach ($node->field_collec_medics['und'] as $medic) {
      $content['infomedic'][] = [
        'title' => $medic['field_salesmedic_title']['und'][0]['value'],
        'body'  => $medic['field_salesmedic_body']['und'][0]['value'],
      ];
    } // endforeach
    // Foreach to collect content to graphics
    foreach ($node->field_sales_grap['und'] as $grap) {
      $content['graphics'][] = [
        'img'   => bem_common_getimg($grap['fid']),
        'title' => $grap['description'],
      ];
    } // endforeach

      // Validacion de PDF
      $pdf = '';
      if (isset($node->field_pdf_descargable['und'][0]['uri'])) {
          $pdf = file_create_url($node->field_pdf_descargable['und'][0]['uri']);
      } // end if

      $content['sales_pdf'] = $pdf;

  } // endif

  return theme('know_why_sales', array('content' => $content));
}

/*
 * Return content to block [know_why_adv]
 * @return theme array ($content)
 */
function bem_knownbp_whyadv() {
  $content = [];

  // Query to Node Content
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_usubtitle', 'sub', 'sub.entity_id = n.nid');
  $query->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $query->leftJoin('field_data_field_multi_imagen', 'img', 'img.entity_id = n.nid');
  $query->condition('n.type', 'knowbp_pb_advgen');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title'])
        ->fields('sub', ['field_usubtitle_value'])
        ->fields('body', ['body_value'])
        ->fields('img', ['field_multi_imagen_fid', 'field_multi_imagen_description']);
  $query->orderBy('n.changed', 'ASC');
  $result = $query->execute()->fetchAll();

  // General Block Content
  if ( !empty($result) ) {
    $content['general'] = [
      'title'    => $result[0]->title,
      'subtitle' => $result[0]->field_usubtitle_value,
      'body'     => $result[0]->body_value,
      'nid'      => $result[0]->nid,
    ];

    foreach ($result as $img) {
      if ( $img->nid == $content['general']['nid'] ) {
        $content['general']['imgs'][] = [
          'img'  => bem_common_getimg($img->field_multi_imagen_fid),
          'name' => $img->field_multi_imagen_description,
        ];

      } // endif
    } // endoforeach
  } // endif

  unset($query);
  // Query to Block Cards
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $query->leftJoin('field_data_field_image', 'img', 'img.entity_id = n.nid');
  $query->leftJoin('field_data_field_uorder', 'orn', 'orn.entity_id = n.nid');
  $query->condition('n.type', 'knowbp_pb_adv');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title'])
        ->fields('body', ['body_value'])
        ->fields('img', ['field_image_fid'])
        ->fields('orn', ['field_uorder_value']);
  $query->orderBy('orn.field_uorder_value', 'ASC');
  $results = $query->execute()->fetchAll();

  // General Block Content
  if ( !empty($results) ) {
    foreach ($results as $node) {
      $content['cards'][] = [
        'title' => $node->title,
        'body'  => $node->body_value,
        'img'   => bem_common_getimg($node->field_image_fid),
      ];
    } // endoforeach
  } // endif

  return theme('know_why_adv', array('content' => $content));
}

function bem_knownbp_whytest(){
  $content = [];

  // Query to Block Cards
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $query->leftJoin('field_data_field_youtube_video', 'yt', 'yt.entity_id = n.nid');
  $query->leftJoin('field_data_field_orden', 'orn', 'orn.entity_id = n.nid');
  $query->condition('n.type', 'testimoniales_de_agentes');
  $query->condition('n.status', 1);
  $query->fields('n', ['nid', 'title'])
        ->fields('body', ['body_value'])
        ->fields('yt', ['field_youtube_video_video_id'])
        ->fields('orn', ['field_orden_value']);
  $query->orderBy('orn.field_orden_value', 'ASC');
  $results = $query->execute()->fetchAll();

  // General Block Content
  if ( !empty($results) ) {
    foreach ($results as $node) {
      $content['test'][] = [
        'title' => $node->title,
        'body'  => $node->body_value,
        'video' => $node->field_youtube_video_video_id,
      ];
    } // endoforeach
  } // endif

  //Block info
  $content['general'] = [
    'title' => variable_get('whybp_testitle', ''),
    'desc'  => variable_get('whybp_testsubt', ''),
  ];
    drupal_add_js(drupal_get_path('module', 'bem_knownbp') . '/js/why.js', array('scope' => 'footer', 'weight' => 8));
  return theme('know_why_test', array('content' => $content));
}

function bem_knownbp_whyknow(){
  $content = [];

  //Block info
  $content = [
    'title' => variable_get('whybp_contitle', ''),
    'desc'  => variable_get('whybp_conbody', ''),
    'pdf'   => bem_common_getimg(variable_get('whybp_pdf', '')),
  ];


  return theme('know_why_know', array('content' => $content));
}
