<?php
/**
 * @file
 * Generate admin forms to module configuration
 */

/**
 * Implements hook_form().
 * Admin form to home blocks 
 * @variable_temp
 *   tools_title
 *   tools_desc
 *   tools_link_txt
 *   tools_link
 */
function bem_home_admin($form, &$form_state){
  // Load temporal variables
  $text_title    = variable_get('tools_title','');
  $text_desc     = variable_get('tools_desc','');
  $text_link_txt = variable_get('tools_link_txt','');
  $text_link     = variable_get('tools_link','');

  /* Admin form */
  $form['home_tools'] = array(
    '#type'        => 'fieldset', 
    '#title'       => 'Bloque de Herramientas',
    '#weight'      => 1,
    '#collapsible' => FALSE, 
    '#collapsed'   => FALSE,
  );
  $form['home_tools']['tools_title'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en el bloque',
    '#default_value' => !empty($text_title) ? $text_title : '',
    '#rows'          => 1,
    '#required'      => TRUE,
  );
  $form['home_tools']['tools_desc'] = array(
    '#type'          => 'textarea',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción que se mostrará en el bloque',
    '#default_value' => !empty($text_desc) ? $text_desc : '',
    '#rows'          => 3,
    '#required'      => TRUE,
  );
  $form['home_tools']['tools_link_txt'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Texto de enlace',
    '#description'   => 'Ingrese el texto que se mostrará en el enlace del bloque',
    '#default_value' => !empty($text_link_txt) ? $text_link_txt : '',
    '#rows'          => 1,
  );
  $form['home_tools']['tools_link'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Enlace',
    '#description'   => 'Ingrese enlace del bloque',
    '#default_value' => !empty($text_link) ? $text_link : '',
    '#rows'          => 1,
  );

  return system_settings_form($form);
}