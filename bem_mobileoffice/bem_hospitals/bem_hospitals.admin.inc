<?php
/**
 * @File Admin "Red de Hospitales"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info Functions to admin forms of admin module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_hospitals_admin() {
  drupal_add_css( drupal_get_path('theme', 'bptheme') . '/admin/admin.css' );
  $form = [];

  // Variables to header
  $title_bann = variable_get('hospitals_head_title','');
  $body_bann  = variable_get('hospitals_head_body','');
  $video_bann = variable_get('hospitals_head_video', '');
  // Variables to Content
  $cont_title  = variable_get('hospitals_content_title','');
  $cont_desc   = variable_get('hospitals_content_desc','');
  $cont_iframe = variable_get('hospitals_content_iframe','');

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
    '#prefix' => '<div class="knowbp-admin"><img src="/'.drupal_get_path('theme', 'bptheme') .'/admin/hospitals_header.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['hospitals_head_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['hospitals_head_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['hospitals_head_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Vídeo',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['hospitals_head_imgd'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_hospitals',
    '#default_value'     => variable_get('hospitals_head_imgd', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['hospitals_head_imgm'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_hospitals',
    '#default_value'     => variable_get('hospitals_head_imgd', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - CONTENT
  $form['intro'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE DE CONTENIDO',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['intro']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="/'.drupal_get_path('theme', 'bptheme') .'/admin/hospitals_content.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['intro']['hospitals_content_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($cont_title) ? $cont_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['intro']['hospitals_content_icon'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Icon SVG',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_hospitals',
    '#default_value'     => variable_get('hospitals_content_icon', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('svg png jpg jpeg'),
    ],
  ];
  $form['intro']['hospitals_content_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Subtítulo',
    '#description'   => 'Subtítulo del bloque',
    '#default_value' => !empty($cont_desc) ? $cont_desc['value'] : '',
    '#rows'          => 2,
    '#format'        => 'plain_text',
  ];
  $form['intro']['hospitals_content_iframe'] = [
    '#type'          => 'text_format',
    '#title'         => 'Frame',
    '#description'   => 'Frame relacionado a red de hospitales',
    '#default_value' => !empty($cont_iframe) ? $cont_iframe['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];

  // Saved permanent files
  $files['module'] = 'bem_hospitals';
  $files['files']  = ['hospitals_head_imgd', 'hospitals_head_imgm', 'hospitals_content_icon'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
