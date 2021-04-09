<?php
/**
 * @File Redesign Grow your Company
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Crece tu Empresa
 * @info Functions to admin forms of module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_growcompany_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to banner
  $title_bann = variable_get('growcompany_title','');
  $body_bann  = variable_get('growcompany_body','');
  $video_bann = variable_get('growcompany_video','');
  // Variables to Articles
  $arts_title = variable_get('growcompany_artstitle','');
  $arts_body  = variable_get('growcompany_artsbody','');
  // Variables to block Resources
  $resources  = variable_get('resources_intro','');


  // FORM - BANNER
  $form['banner'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BANNER',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['banner']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/growcompany_bn.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['growcompany_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['growcompany_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['growcompany_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Video',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['growcompany_imgdesk'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('growcompany_imgdesk', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['growcompany_imgmob'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('growcompany_imgmob', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - ARTICLES
  $form['arts'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE ARTICULOS',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['arts']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/growcompany_arts.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['arts']['growcompany_artstitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($arts_title) ? $arts_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['arts']['growcompany_artsbody'] = [
    '#type'          => 'text_format',
    '#title'         => 'Introducción',
    '#description'   => 'Contenido introductorio. Es posible utilizar código HTML.<br>Se recomienda hacer la carga de archivos dentro de <a href="/admin/content/file">FILES<a>',
    '#default_value' => !empty($arts_body) ? $arts_body['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  // FORM - RECURSOS
  /*
  $form['intro'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE RECURSOS',
    '#weight'      => 3,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['intro']['resources_intro'] = [
    '#type'          => 'text_format',
    '#title'         => 'Introducción',
    '#description'   => 'Contenido introductorio.',
    '#default_value' => !empty($resources) ? $resources['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];*/

  // Saved permanent files
  $files['module'] = 'bem_growcompany';
  $files['files']  = ['growcompany_imgdesk', 'growcompany_imgmob', 'growcompany_introsvg'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  } // endif
}

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_growcompany_adminblock() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  $resources  = variable_get('resources_intro','');

  // FORM - RECURSOS
  $form['intro'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE RECURSOS',
    '#weight'      => 3,
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  ];
  $form['intro']['resources_intro'] = [
    '#type'          => 'text_format',
    '#title'         => 'Introducción',
    '#description'   => 'Contenido introductorio.',
    '#default_value' => !empty($resources) ? $resources['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  $form['intro']['growcompany_introsvg'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('growcompany_introsvg', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('svg png jpg jpeg'),
    ],
  ];


  // Saved permanent files
  $files['module'] = 'bem_growcompany';
  $files['files']  = ['growcompany_introsvg'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  } // endif
}
