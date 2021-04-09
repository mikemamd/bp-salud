<?php
/**
 * @File Admin "Conoce BP"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD
 * @info Functions to admin forms of module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_knowbp_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  $title_bann = variable_get('knowbp_title','');
  $body_bann  = variable_get('knowbp_body','');
  $intro      = variable_get('knowbp_intro','');
  $video_bann = variable_get('knowbp_video', '');

  // FORM - BANNER
  $form['banner'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BANNER',
    '#weight'      => 1,
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  ];
  $form['banner']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/knowbp_banner.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['knowbp_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['knowbp_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['knowbp_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Vídeo',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['knowbp_imgdesk'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_knowbp',
    '#default_value'     => variable_get('knowbp_imgdesk', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['knowbp_imgmob'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_knowbp',
    '#default_value'     => variable_get('knowbp_imgmob', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - INTRO
  // ** Disabled this content by CLIENTE **
  /*
  $form['intro'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE INTRO',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['intro']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/knowbp_intro.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['intro']['knowbp_intro'] = [
    '#type'          => 'text_format',
    '#title'         => 'Introducción',
    '#description'   => 'Contenido introductorio. Es posible utilizar código HTML.<br>Se recomienda hacer la carga de archivos dentro de <a href="/admin/content/file">FILES<a>',
    '#default_value' => !empty($intro) ? $intro['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
*/
  // Saved permanent files
  $files['module'] = 'bem_knowbp';
  $files['files']  = ['knowbp_imgdesk', 'knowbp_imgmob'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}

/**
 * Implements hook_form()
 * Make a admin form to "WHO IS bp"
 */
function bem_knowbp_whoisbp() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  $str_title = variable_get('whoisbp_strtitle','');
  $str_body  = variable_get('whoisbp_strbody','');
  $pru_title = variable_get('whoisbp_pruptitle','');
  $pru_body  = variable_get('whoisbp_prupbody','');

  // FORM - STRUCTURE
  $form['structure'] = [
    '#type'        => 'fieldset',
    '#title'       => 'BLOQUE | ESTRUCTURA ORGANIZACIONAL',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['structure']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/whois_structure.jpg">',
    '#suffix' => '<p>EJEMPLO DE CONTENIDO DE BLOQUE</p></div>',
  ];
  $form['structure']['whoisbp_strtitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($str_title) ? $str_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['structure']['whoisbp_strbody'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($str_body) ? $str_body['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  // FORM - PRUPOSE
  $form['prupose'] = [
    '#type'        => 'fieldset',
    '#title'       => 'BLOQUE | NUESTRO PROPÓSITO',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['prupose']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/whois_vision.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO </p></div>',
  ];
  $form['prupose']['whoisbp_pruptitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($pru_title) ? $pru_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['prupose']['whoisbp_prupbody'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($pru_body) ? $pru_body['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['prupose']['whoisbp_img'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen Titular',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_knowbp',
    '#default_value'     => variable_get('whoisbp_img', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];

  // Saved permanent files
  $files['module'] = 'bem_knowbp';
  $files['files']  = ['whoisbp_img'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}

/**
 * Implements hook_form()
 * Make a admin form to "WHY bp"
 */
function bem_knowbp_whybp() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  $vent_title  = variable_get('whybp_ventitle','');
  $vent_body   = variable_get('whybp_ventbody','');
  $vent_footer = variable_get('whybp_ventfooter','');
  $test_title  = variable_get('whybp_testitle','');
  $test_subt   = variable_get('whybp_testsubt','');
  $pru_title   = variable_get('whybp_contitle','');
  $pru_body    = variable_get('whybp_conbody','');


  // FORM - ADVANTAGES
  /*
  $form['advantages'] = [
    '#type'        => 'fieldset',
    '#title'       => 'BLOQUE | VENTAJAS COMPETITIVAS',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['advantages']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/why_advantages.jpg">',
    '#suffix' => '<p>EJEMPLO DE CONTENIDO DE BLOQUE</p></div>',
  ];
  $form['advantages']['whybp_ventitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($vent_title) ? $vent_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['advantages']['whybp_ventbody'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($vent_body) ? $vent_body['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['advantages']['whybp_ventfooter'] = [
    '#type'          => 'text_format',
    '#title'         => 'Footer',
    '#description'   => 'Footer en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($vent_body) ? $vent_body['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['advantages']['footer'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/why_advantages_footer.jpg">',
    '#suffix' => '<p>EJEMPLO DE CONTENIDO DE FOOTER</p></div>',
  ];  */
  // FORM - TESTIMONIALS
  $form['testimonials'] = [
    '#type'        => 'fieldset',
    '#title'       => 'BLOQUE | TESTIMONIALES DE AGENTES',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['testimonials']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/why_testimonials.jpg">',
    '#suffix' => '<p>EJEMPLO DE CONTENIDO DE BLOQUE</p></div>',
  ];
  $form['testimonials']['whybp_testitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($test_title) ? $test_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['testimonials']['whybp_testsubt'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($test_subt) ? $test_subt['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  // FORM - KNOW
  $form['know'] = [
    '#type'        => 'fieldset',
    '#title'       => 'BLOQUE | CONOCE MÁS DE bp',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['know']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/why_know.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO </p></div>',
  ];
  $form['know']['whybp_contitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($pru_title) ? $pru_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['know']['whybp_conbody'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($pru_body) ? $pru_body['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['know']['whybp_pdf'] = [
    '#type'              => 'managed_file',
    '#title'             => 'PDF ADJUNTO',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_knowbp',
    '#default_value'     => variable_get('whybp_pdf', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('pdf'),
    ],
  ];

  // Saved permanent files
  $files['module'] = 'bem_knowbp';
  $files['files']  = ['whybp_pdf'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
