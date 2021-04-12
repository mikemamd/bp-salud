<?php
/**
 * @File Admin "Guía de Ventas"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package 'BP - SALUD | Oficina Móvil'
 * @info Functions to admin forms of admina module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_salesguide_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to header
  $title_bann = variable_get('salesguide_head_title','');
  $body_bann  = variable_get('salesguide_head_body','');
  $video_bann = variable_get('salesguide_head_video', '');
  // Variables to Step One
  $stepone_title  = variable_get('salesguide_stepone_title','');
  $stepone_stitle = variable_get('salesguide_stepone_stitle','');
  $stepone_desc   = variable_get('salesguide_stepone_desc', '');
  // Variables to Step Two
  $steptwo_title  = variable_get('salesguide_steptwo_title','');
  $steptwo_stitle = variable_get('salesguide_steptwo_stitle','');
  $steptwo_desc   = variable_get('salesguide_steptwo_desc', '');
  // Variables to Step Three
  $stepthree_title    = variable_get('salesguide_stepthree_title','');
  $stepthree_stitle   = variable_get('salesguide_stepthree_stitle','');
  $stepthree_desc     = variable_get('salesguide_stepthree_desc', '');
  $stepthree_contdesc = variable_get('salesguide_stepthree_contdesc', '');
  $stepthree_contlink = variable_get('salesguide_stepthree_contlink', '');


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
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/salesguide_header.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['salesguide_head_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['salesguide_head_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['salesguide_head_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Vídeo',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['salesguide_head_imgd'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_salesguide',
    '#default_value'     => variable_get('salesguide_head_imgd', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['salesguide_head_imgm'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_salesguide',
    '#default_value'     => variable_get('salesguide_head_imgm', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - STEP ONE
  $form['stepone'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE PASO 1',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['stepone']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/salesguide_step1.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['stepone']['salesguide_stepone_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($stepone_title) ? $stepone_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['stepone']['salesguide_stepone_stitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($stepone_stitle) ? $stepone_stitle['value'] : '',
    '#rows'          => 2,
    '#format'        => 'plain_text',
  ];
  $form['stepone']['salesguide_stepone_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($stepone_desc) ? $stepone_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  // FORM - STEP TWO
  $form['steptwo'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE PASO 2',
    '#weight'      => 3,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['steptwo']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/salesguide_step2.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['steptwo']['salesguide_steptwo_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($steptwo_title) ? $steptwo_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['steptwo']['salesguide_steptwo_stitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($steptwo_stitle) ? $steptwo_stitle['value'] : '',
    '#rows'          => 2,
    '#format'        => 'plain_text',
  ];
  $form['steptwo']['salesguide_steptwo_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($steptwo_desc) ? $steptwo_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  // FORM - STEP THREE
  $form['stepthree'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE PASO 3',
    '#weight'      => 4,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['stepthree']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/salesguide_step3.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['stepthree']['salesguide_stepthree_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($stepthree_title) ? $stepthree_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['stepthree']['salesguide_stepthree_stitle'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($stepthree_stitle) ? $stepthree_stitle['value'] : '',
    '#rows'          => 2,
    '#format'        => 'plain_text',
  ];
  $form['stepthree']['salesguide_stepthree_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($stepthree_desc) ? $stepthree_desc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];

  // FORM - STEP THREE
  $form['stepthree']['salesguide_content'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONTENIDO BLOQUE PASO 3',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['stepthree']['salesguide_content']['salesguide_stepthree_contimg'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Icono de contenido',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_salesguide',
    '#default_value'     => variable_get('salesguide_stepthree_contimg', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('svg png jpg jpeg'),
    ],
  ];
  $form['stepthree']['salesguide_content']['salesguide_stepthree_contdesc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque. Es posible añadir código HTML para una ocntenido más personalizado',
    '#default_value' => !empty($stepthree_contdesc) ? $stepthree_contdesc['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];
  $form['stepthree']['salesguide_content']['salesguide_stepthree_contlink'] = [
    '#type'          => 'text_format',
    '#title'         => 'Enlace',
    '#description'   => 'Enlace del bloque',
    '#default_value' => !empty($stepthree_contlink) ? $stepthree_contlink['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];

  // Saved permanent files
  $files['module'] = 'bem_salesguide';
  $files['files']  = ['salesguide_head_imgd', 'salesguide_head_imgm', 'salesguide_stepthree_contimg'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
