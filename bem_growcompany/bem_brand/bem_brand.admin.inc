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
function bem_brand_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to banner
  $title_bann = variable_get('brand_banner_title','');
  $body_bann  = variable_get('brand_banner_body','');
  $video_bann = variable_get('brand_banner_video','');
  // Variables to titles of blocks
  $keys       = variable_get('brand_keys','');
  $brand      = variable_get('brand_brand','');
  $slide      = variable_get('brand_slide','');

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
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/brand_banner.jpg">',
    '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
  ];
  $form['banner']['brand_banner_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['brand_banner_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['brand_banner_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Video',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['brand_imgdesk'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('brand_imgdesk', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['brand_imgmob'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_growcompany',
    '#default_value'     => variable_get('brand_imgmob', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  // FORM - KEYS
  $form['keys'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE CLAVES PARA CRECER TU MARCA',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['keys']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/brand_keys.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['keys']['brand_keys'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en blque. Es posible utilizar código HTML.',
    '#default_value' => !empty($keys) ? $keys['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  // FORM - BRAND
  $form['brand'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE CONSTRUYENDO UNA MARCA',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['brand']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/brand_brand.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['brand']['brand_brand'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en blque. Es posible utilizar código HTML.',
    '#default_value' => !empty($brand) ? $brand['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  // FORM - SLIDE
  $form['slide'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BLOQUE CRECE TU MARCA (SLIDER)',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['slide']['markup'] = [
    '#type'   => 'markup',
    '#prefix' => '<div class="knowbp-admin"><img src="'.$base_url.'/sites/all/themes/zen/bp/new-theme/admin/brand_slider.jpg">',
    '#suffix' => '<p>EJEMPLO DE BLOQUE DE CONTENIDO</p></div>',
  ];
  $form['slide']['brand_slide'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en blque. Es posible utilizar código HTML.',
    '#default_value' => !empty($slide) ? $slide['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];

  // Saved permanent files
  $files['module'] = 'bem_brand';
  $files['files']  = ['brand_imgdesk', 'brand_imgmob'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
