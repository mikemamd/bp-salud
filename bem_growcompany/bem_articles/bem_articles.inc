<?php
/**
 * @File Redesign Articles
 * @author Miguel Martínez <miguel.martinez@ogilvy.com>
 * @package BUPA - Redesign V2
 * @info This module contains functions to blocks on section Articles
 * @vertion dev 1.0.0.0
 */

/**
 * Return filters to blocks
 * @see bem_articles_block_view
 * @return theme array ($content)
 */
function bem_articles_getfilter() {

  $params = drupal_get_query_parameters();
  (int) $filter = (isset($params['fl']))? $params['fl'] : '';


  // Obtener todos los copys de capacitaciones
  $copys = bupa_banner_page_copys_results("capacitaciones_page");

  $content = [];

  // Texto del título de capacitaciones
  $content['title']['value'] = (isset($copys[0]['text'])) ? $copys[0]['text'] : '';

  // Load Vocab
  $vocab = taxonomy_vocabulary_machine_name_load('content_articles');
  $vid   = $vocab->vid;
  // Query to get terms
  $qry = db_select('taxonomy_term_data', 'ttd');
  $qry->condition('ttd.vid', $vid, '=');
  $qry->fields('ttd', ['tid', 'name', 'description']);
  $qry->orderBy('weight', 'ASC');
  $results = $qry->execute()->fetchAll();

    if (!empty($results)) {
        foreach ($results as $result) {
            $content['f_type'][$result->description] = [
                'name' => $result->name,
                'tid'  => $result->tid,
                'checked' => ($filter == $result->tid) ? TRUE : FALSE,
            ];
        }
    }
  // Destroy variables to new use
  unset($vocab);
  unset($vid);
  unset($qry);
  unset($results);
  unset($result);

  // Load Vocab
  $vocab = taxonomy_vocabulary_machine_name_load('categoria_documentos_interes');
  $vid   = $vocab->vid;
  // Query to get terms
  $qry = db_select('taxonomy_term_data', 'ttd');
  $qry->condition('ttd.vid', $vid, '=');
  $qry->fields('ttd', ['tid', 'name', 'description']);
  $qry->orderBy('weight', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {  
      $content['f_type']['documentos_de_inter_s_']['sub'][$result->tid] = $result->name;
    }
  }
  // Destroy variables to new use
  unset($vocab);
  unset($vid);
  unset($qry);
  unset($results);
  unset($result);

  // Load Vocab to second filter
  $vocab = taxonomy_vocabulary_machine_name_load('type_articles');
  $vid   = $vocab->vid;
  // Query to get terms
  $qry = db_select('taxonomy_term_data', 'ttd');
  $qry->condition('ttd.vid', $vid, '=');
  $qry->fields('ttd', ['tid', 'name', 'description']);
  $qry->orderBy('weight', 'ASC');
  $results = $qry->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {  
      $content['f_category'][$result->tid] = $result->name;
    }
  }

  return theme('bem_filter_arts', array('content' => $content));
}
