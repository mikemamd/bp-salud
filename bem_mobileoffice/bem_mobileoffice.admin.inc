<?php
/**
 * @File Admin "Guía de Ventas"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info Functions to admin forms of admina module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_mobileoffice_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to header
  $title_bann = variable_get('mobileoffice_head_title','');
  $body_bann  = variable_get('mobileoffice_head_body','');
  $video_bann = variable_get('mobileoffice_head_video', '');
  // Variables to block tools
  $tools_title = variable_get('mobileoffice_tools_title','');
  $tools_desc  = variable_get('mobileoffice_tools_body','');
  // Variables to block testimonials
  $client_title = variable_get('mobileoffice_client_title','');
  $client_desc  = variable_get('mobileoffice_client_body','');
  // Variable to resources
  $resources = variable_get('mobileoffice_intro','');

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
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/mobile_office_banner.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['mobileoffice_head_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['mobileoffice_head_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['mobileoffice_head_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Vídeo',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['mobileoffice_head_imgd'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_mobileoffice',
    '#default_value'     => variable_get('mobileoffice_head_imgd', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['mobileoffice_head_imgm'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_mobileoffice',
    '#default_value'     => variable_get('mobileoffice_head_imgm', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['mobileoffice_intro'] = [
    '#type'          => 'text_format',
    '#title'         => 'Introducción (BLOQUE DE RECURSOS)',
    '#description'   => 'Contenido introductorio.',
    '#default_value' => !empty($resources) ? $resources['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  $form['banner']['mobileoffice_introsvg'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen (BLOQUE DE RECURSOS)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_mobileoffice',
    '#default_value'     => variable_get('mobileoffice_introsvg', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('svg png jpg jpeg'),
    ],
  ];

  // FORM - TOOLS
  $form['tools'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE HERRAMIENTAS',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['tools']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/mobile_office_tools.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['tools']['mobileoffice_tools_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($tools_title) ? $tools_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['tools']['mobileoffice_tools_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($tools_desc) ? $tools_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  // FORM - TESTIMONIALS
  $form['clients'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE TESTIMONIALES DE CLIENTES',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['clients']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/mobile_office_clients.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['clients']['mobileoffice_client_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($client_title) ? $client_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['clients']['mobileoffice_client_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($client_desc) ? $client_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];


  // Saved permanent files
  $files['module'] = 'bem_mobileoffice';
  $files['files']  = ['mobileoffice_head_imgd', 'mobileoffice_head_imgm', 'mobileoffice_introsvg'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
