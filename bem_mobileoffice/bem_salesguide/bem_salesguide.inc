<?php
/**
 * @File Redesign "Oficina Móvil"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info Functions to return content to blocks
 * @vertion dev 1.0.0.0
 */

/**
 * Return content to block [salesguide_stepone]
 * @return theme array ($content)
 */
function bem_salesguide_stepone(){
  $content = $info = [];
  // Load Vocab
  $vocab = taxonomy_vocabulary_machine_name_load('salesguide_icons');
  $vid   = $vocab->vid;
  // Query to get terms
  $qry = db_select('taxonomy_term_data', 'tx');
  $qry->leftJoin('field_data_field_icon_svg', 'svg', 'svg.entity_id = tx.tid');
  $qry->condition('tx.vid', $vid, '=');
  $qry->fields('tx', ['tid', 'name', 'description'])
      ->fields('svg', ['field_icon_svg_fid']);
  $qry->orderBy('weight', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {
      $content[] = [
        'tid'  => $result->tid,
        'name' => $result->name,
        'desc' => $result->description,
        'icon' => !empty($result->field_icon_svg_fid) ? bem_common_getimg($result->field_icon_svg_fid) : '',
      ];
    }
    // Group array by cols
    $content = array_chunk($content, 3);
  }

  // Make array with block info
  $info['title']  = variable_get('salesguide_stepone_title','');
  $info['stitle'] = variable_get('salesguide_stepone_stitle','');
  $info['desc']   = variable_get('salesguide_stepone_desc', '');

  return theme('salesguide_stepone', array('content' => $content, 'info' => $info));
}

/**
 * Return content to block [salesguide_stepone]
 * @return theme array ($content)
 */
function bem_salesguide_steptwo() {
  global $base_url;
  $content = [];

  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder', 'ord', 'ord.entity_id = n.nid');
  $qry->leftJoin('field_data_field_icon_svg', 'svg', 'svg.entity_id = n.nid');
  $qry->leftJoin('field_data_field_bemcollect_cards', 'collect', 'collect.entity_id = n.nid');
  $qry->condition('n.type', 'salesguide_profiles');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('svg', ['field_icon_svg_fid'])
      ->fields('collect', ['field_bemcollect_cards_field_usubtitle_value', 'field_bemcollect_cards_field_body_value', 'field_bemcollect_cards_field_icon_svg_fid', 'field_bemcollect_cards_id']);
  $qry->orderBy('ord.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  // Each array to structure content
  foreach ($results as $key => $node) {
    // Make array with cards info
    $cards[$node->nid][] = [
      'title' => $node->field_bemcollect_cards_field_usubtitle_value,
      'desc'  => $node->field_bemcollect_cards_field_body_value,
      'icon'  => bem_common_getimg($node->field_bemcollect_cards_field_icon_svg_fid),
      'id'    => $node->field_bemcollect_cards_id,
    ];

    // Make array with node content
    $content[$node->nid] = [
      'title' => $node->title,
      'desc'  => $node->body_value,
      'icon'  => bem_common_getimg($node->field_icon_svg_fid),
    ];

  } // endforeach

  foreach ($cards as $nid => $item) {
    $content[$nid]['cards'] = $item;
  } // endforeach


  // Make array with block info
  $info['title']  = variable_get('salesguide_steptwo_title','');
  $info['stitle'] = variable_get('salesguide_steptwo_stitle','');
  $info['desc']   = variable_get('salesguide_steptwo_desc', '');

  return theme('salesguide_steptwo', array('content' => $content, 'info' => $info));
}

/**
 * Return content to block [salesguide_stepthree]
 * @return theme array ($content)
 */
function bem_salesguide_stepthree() {
  $content = [
    'body' => variable_get('salesguide_stepthree_contdesc',''),
    'path' => variable_get('salesguide_stepthree_contlink',''),
    'icon' => bem_common_getimg(variable_get('salesguide_stepthree_contimg', '')),
  ];

  // Make array with block info
  $info['title']  = variable_get('salesguide_stepthree_title','');
  $info['stitle'] = variable_get('salesguide_stepthree_stitle','');
  $info['desc']   = variable_get('salesguide_stepthree_desc', '');

  return theme('salesguide_stepthree', array('content' => $content, 'info' => $info));
}
