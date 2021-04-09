<?php
/**
 * @File Redesign Brand
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Crece tu Empresa
 * @info This module contains functions to blocks on section Brand
 * @vertion dev 1.0.0.0
 */

/**
 * Return content to blocks by delta
 * @see bem_brand_block_view
 * @param string ($delta) machine name of block to display
 *   bem_brand_keys
 *   bem_brand_make
 * @return theme array ($content) by $delta
 */
function bem_brand_getcontent($delta) {
  $content = [];
  $ntype   = ['bem_brand_keys' => 'bem_brandupkey', 'bem_brand_make' => 'bem_brandmake',];

  // Query to get content
  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body',           'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_icon_svg', 'img', 'img.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder',   'ordr', 'ordr.entity_id = n.nid');
  $qry->condition('n.type', $ntype[$delta]);
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('img', ['field_icon_svg_fid']);
  $qry->orderBy('ordr.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  // Structure content
  if ( !empty($results) ) {
    foreach ($results as $value) {
      $content['block'][] = [
        'title' => $value->title,
        'body'  => $value->body_value,
        'img'   => bem_common_getimg($value->field_icon_svg_fid),
      ];
    } // endforeach

    // Get block title
    $title = ( $delta == 'bem_brand_keys' ) ? 'brand_keys' : 'brand_brand';
    $content['title']  = variable_get($title,'');

  } // endif

  return theme($delta, array('content' => $content));
}

/**
 * Return content to blocks [bem_brand_slide]
 * @return theme array ($content) by $delta
 * @see bem_brand_block_view
 * @return theme array ($content)
 */
function bem_brand_getslide() {
  $content = [];

  // Query to get content
  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_field_body',      'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uimg_desk', 'imgd', 'imgd.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uimg_mob',  'imgm', 'imgm.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder',    'ordr', 'ordr.entity_id = n.nid');
  $qry->condition('n.type', 'bem_brandslide');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['field_body_value'])
      ->fields('imgd', ['field_uimg_desk_fid'])
      ->fields('imgm', ['field_uimg_mob_fid']);
  $qry->orderBy('ordr.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  // Structure content
  if ( !empty($results) ) {
    foreach ($results as $value) {
      $content['block'][] = [
        'títle' => $value->title,
        'body'  => $value->field_body_value,
        'imgd'  => bem_common_getimg($value->field_uimg_desk_fid),
        'imgm'  => bem_common_getimg($value->field_uimg_mob_fid),
      ];
    } // endforeach

    $content['title'] = variable_get('brand_slide','');
  } // endif

  return theme('bem_brand_slide', array('content' => $content));
}
