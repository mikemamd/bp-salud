<?php
/**
 * @File Redesign Ethics Code
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Crece tu Empresa
 * @info This module contains functions to blocks on section Ethics Code
 * @vertion dev 1.0.0.0
 */

/**
 * Return content to intro block
 * @see bem_ethicscode_view
 * @return theme array ($content)
 */
function bem_ethicscode_getintro() {
  $content = [];

  // Query to get content
  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body',            'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uimg_desk', 'img', 'img.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder',    'ordr', 'ordr.entity_id = n.nid');
  $qry->condition('n.type', 'ethics_intro');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('img', ['field_uimg_desk_fid']);
  $qry->orderBy('ordr.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  // Structure content
  if ( !empty($results) ) {
    foreach ($results as $value) {
      $content[] = [
        'title' => $value->title,
        'body'  => $value->body_value,
        'img'   => bem_common_getimg($value->field_uimg_desk_fid),
      ];
    } // endforeach
  } // endif

  return theme('ethicscode_intro', array('content' => $content));
}

/**
 * Return content to Benefits block
 * @see bem_ethicscode_view
 * @return theme array ($content)
 */
function bem_ethicscode_getbenefits() {
  $content = [];
  // Load variables to block
  $content['block']['title'] = variable_get('ethics_bene_title','');

  // Query to get content
  $qry = db_select('node', 'n');
  $qry->leftJoin('field_data_body',           'body', 'body.entity_id = n.nid');
  $qry->leftJoin('field_data_field_icon_svg', 'img', 'img.entity_id = n.nid');
  $qry->leftJoin('field_data_field_uorder',   'ordr', 'ordr.entity_id = n.nid');
  $qry->condition('n.type', 'ethics_benefits');
  $qry->condition('n.status', 1);
  $qry->fields('n', ['nid', 'title'])
      ->fields('body', ['body_value'])
      ->fields('img', ['field_icon_svg_fid']);
  $qry->orderBy('ordr.field_uorder_value', 'ASC');
  $results = $qry->execute()->fetchAll();

  // Structure content
  if ( !empty($results) ) {
    foreach ($results as $value) {
      $content['content'][] = [
        'title' => $value->title,
        'body'  => $value->body_value,
        'img'   => bem_common_getimg($value->field_icon_svg_fid),
      ];
    } // endforeach
  } // endif

  return theme('ethicscode_benefits', array('content' => $content));
}
