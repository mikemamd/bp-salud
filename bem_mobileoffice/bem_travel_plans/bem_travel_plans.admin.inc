<?php
/**
 * @File Admin "Planes de Viaje"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info Functions to admin forms of admin module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_travel_plans_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to header
  $title_bann = variable_get('travel_head_title','');
  $body_bann  = variable_get('travel_head_body','');
  $video_bann = variable_get('travel_head_video', '');
  // Variables to intro
  $intro_title = variable_get('travel_intro_title','');
  $intro_intro = variable_get('travel_intro_intro','');
  $intro_desc  = variable_get('travel_intro_desc','');
  // Variables to plans
  $plans_title = variable_get('travel_plans_title','');
  $plans_desc  = variable_get('travel_plans_desc','');
  // Variables to materials
  $files_title = variable_get('travel_files_title','');
  $files_desc  = variable_get('travel_files_desc','');

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
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/travel_header.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['travel_head_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['travel_head_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['travel_head_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Vídeo',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['travel_head_imgd'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_travel_plans',
    '#default_value'     => variable_get('travel_head_imgd', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['travel_head_imgm'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_travel_plans',
    '#default_value'     => variable_get('travel_head_imgm', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - INTRO
  $form['intro'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE INTRO',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['intro']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/travel_intro.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['intro']['travel_intro_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($intro_title) ? $intro_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['intro']['travel_intro_intro'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($intro_intro) ? $intro_intro['value'] : '',
    '#rows'          => 2,
    '#format'        => 'plain_text',
  ];
  $form['intro']['travel_intro_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($intro_desc) ? $intro_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  $form['intro']['travel_intro_img'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de Contenido',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_travel_plans',
    '#default_value'     => variable_get('travel_intro_img', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - PLANS
  $form['planes'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE PLANES',
    '#weight'      => 3,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['planes']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/travel_plans.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['planes']['travel_plans_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($plans_title) ? $plans_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['planes']['travel_plans_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($plans_desc) ? $plans_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  // FORM - PLANS
  $form['files'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE MATERIALES DE DESCARGA',
    '#weight'      => 4,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['files']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/travel_files.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['files']['travel_files_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($files_title) ? $files_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['files']['travel_files_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($files_desc) ? $files_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  $form['files']['travel_files_svg'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de Contenido',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/travel_files_svg',
    '#default_value'     => variable_get('travel_files_svg', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('svg png jpg jpeg'),
    ],
  ];

  // Saved permanent files
  $files['module'] = 'bem_travel_plans';
  $files['files']  = ['travel_head_imgd', 'travel_head_imgm', 'travel_intro_img', 'travel_files_svg'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
