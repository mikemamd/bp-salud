<?php
/**
 * @File Admin "Biblioteca"
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BP - SALUD | Oficina Móvil
 * @info Functions to admin forms of admina module
 * @vertion dev 1.0.0.0
 */

/**
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_library_admin() {
  global $base_url;
  drupal_add_css( drupal_get_path('theme', 'bp') . '/new-theme/admin/admin.css' );
  $form = [];

  // Variables to header
  $title_bann = variable_get('library_head_title','');
  $body_bann  = variable_get('library_head_body','');
  $video_bann = variable_get('library_head_video', '');
  // Variables to filter
  $filter_title = variable_get('library_filter_title','');
  $filter_desc  = variable_get('library_filter_desc', '');
  // Variables to interest documents
  $interest_title = variable_get('library_interest_title','');
  $interest_desc  = variable_get('library_interest_desc', '');
  // Variables to financial Three
  $financial_title = variable_get('library_financial_title','');
  $financial_desc  = variable_get('library_financial_desc','');

  // FORM - BANNER
  $form['banner'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BANNER',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['banner']['library_head_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['library_head_body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
    '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['library_head_video'] = [
    '#type'          => 'text_format',
    '#title'         => 'Vídeo',
    '#description'   => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
    '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['library_head_imgd'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Desktop)',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/bem_salesguide',
    '#default_value'     => variable_get('library_head_imgd', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];
  $form['banner']['library_head_imgm'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de banner (Mobile)',
    '#required'          => FALSE,
    '#upload_location'   => file_default_scheme() . '://module/bem_salesguide',
    '#default_value'     => variable_get('library_head_imgm', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];

  // FORM - FILTERS
  $form['filter'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | FILTROS',
    '#weight'      => 2,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['filter']['library_filter_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($filter_title) ? $filter_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['filter']['library_filter_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque',
    '#default_value' => !empty($filter_desc) ? $filter_desc['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];

  // FORM - DOCS INTEREST
  $form['interest'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | DOCUMENTOS DE INTERÉS',
    '#weight'      => 3,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['interest']['library_interest_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($interest_title) ? $interest_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['interest']['library_interest_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque',
    '#default_value' => !empty($interest_desc) ? $interest_desc['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];

  // FORM - DOCS INTEREST
  $form['financial'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | DOCUMENTOS DE FINANCIEROS',
    '#weight'      => 3,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['financial']['library_financial_title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título de Bloque',
    '#description'   => 'Título resaltado que aparecerá en el bloque',
    '#default_value' => !empty($financial_title) ? $financial_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['financial']['library_financial_desc'] = [
    '#type'          => 'text_format',
    '#title'         => 'Descripción',
    '#description'   => 'Descripción del bloque',
    '#default_value' => !empty($financial_desc) ? $financial_desc['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];

  // Saved permanent files
  $files['module'] = 'bem_library';
  $files['files']  = ['library_head_imgm', 'library_head_imgd'];
  $status          = bem_common_fileperm($files);
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}
