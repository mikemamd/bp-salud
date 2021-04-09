<?php
/**
 * @File Redesign Your Brand
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Crece tu Empresa
 * @info Functions to admin forms of module
 * @vertion dev 1.0.0.0
 */

/*
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_ethicscode_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to banner
  $title_bann = variable_get('ethics_banner_title','');
  $body_bann  = variable_get('ethics_banner_body','');
  $video_bann = variable_get('ethics_banner_video','');
  // Variables to benefits
  $title_bene = variable_get('ethics_bene_title','');
  // Variables to program
  $title_pro  = variable_get('ethics_pro_title','');
  $body_pro   = variable_get('ethics_pro_body','');
  $desc_pro   = variable_get('ethics_pro_desc','');

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
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/ethicscode_banner.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['ethics_banner_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['ethics_banner_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['ethics_banner_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Video',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['ethics_imgdesk'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('ethics_imgdesk', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['ethics_imgmob'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('ethics_imgmob', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - BENEFITS
  $form['benefits'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE BENEFICIOS',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['benefits']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/ethicscode_benefits.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['benefits']['ethics_bene_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en blque. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bene) ? $title_bene['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  // FORM - PROGRAM
  $form['program'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE PROGRAMA DE CUMPLIMIENTO',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['program']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/ethicscode_program.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['program']['ethics_pro_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_pro) ? $title_pro['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['program']['ethics_pro_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción que aparecerá en el blocque. Es posible utilizar código HTML.',
    '#default_value' => !empty($desc_pro) ? $desc_pro['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['program']['ethics_pro_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Contenido del bloque. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_pro) ? $body_pro['value'] : '',
    '#rows'          => 5,
    '#format'        => 'plain_text',
  ];

  // Saved permanent files
  $files['module'] = 'bem_ethicscode';
  $files['files']  = ['ethics_imgdesk', 'ethics_imgmob'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
