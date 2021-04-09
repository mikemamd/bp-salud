<?php
/**
 * @File Redesign Articles
 * @author Miguel Martínez <miguel.martinez@ogilvy.com>
 * @package BUPA - Redesign V2
 * @info Functions to admin forms of module
 * @vertion dev 1.0.0.0
 */

/*
 * Implements hook_form()
 * Make a admin form to general settings in module
 */
function bem_articles_admin()
{

    $nid = bem_common_get_nid_by_alias("settings-banner-capacitaciones");
    drupal_goto('node/' . $nid->nid . '/edit');


    global $base_url;
    drupal_add_css(drupal_get_path('theme', 'bupa') . '/new-theme/admin/admin.css');
    $form = [];

    // Variables to banner
    $title_bann = variable_get('arts_banner_title', '');
    $body_bann = variable_get('arts_banner_body', '');
    $video_bann = variable_get('arts_banner_video', '');
    // Variables to titles of blocks
    $filter = variable_get('arts_filter_title', '');

    // FORM - BANNER
    $form['banner'] = [
        '#type' => 'fieldset',
        '#title' => 'CONFIGURACIÓN | BANNER',
        '#weight' => 1,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    ];
    $form['banner']['markup'] = [
        '#type' => 'markup',
        '#prefix' => '<div class="knowbupa-admin"><img src="' . $base_url . '/sites/all/themes/zen/bupa/new-theme/admin/brand_banner.jpg">',
        '#suffix' => '<p>EJEMPLIFICACIÓN DE BANNER</p></div>',
    ];
    $form['banner']['arts_banner_title'] = [
        '#type' => 'text_format',
        '#title' => 'Título',
        '#description' => 'Título que se mostrará en banner. Es posible utilizar código HTML.',
        '#default_value' => !empty($title_bann) ? $title_bann['value'] : '',
        '#rows' => 1,
        '#format' => 'plain_text',
    ];
    $form['banner']['arts_banner_body'] = [
        '#type' => 'text_format',
        '#title' => 'Body',
        '#description' => 'Descripción que aparecerá en Banner. Es posible utilizar código HTML.',
        '#default_value' => !empty($body_bann) ? $body_bann['value'] : '',
        '#rows' => 3,
        '#format' => 'plain_text',
    ];
    $form['banner']['arts_banner_video'] = [
        '#type' => 'text_format',
        '#title' => 'Vídep',
        '#description' => 'Ingrese URL desde YouTube para agregar un vídeo. <b>Es campo tendrá prioridad sobre una imagen</b>',
        '#default_value' => !empty($video_bann) ? $video_bann['value'] : '',
        '#rows' => 1,
        '#format' => 'plain_text',
    ];
    $form['banner']['arts_imgdesk'] = [
        '#type' => 'managed_file',
        '#title' => 'Imagen de banner (Desktop)',
        '#required' => TRUE,
        '#upload_location' => file_default_scheme() . '://module/bem_articles',
        '#default_value' => variable_get('arts_imgdesk', ''),
        '#upload_validators' => [
            'file_validate_extensions' => array('png jpg jpeg'),
        ],
    ];
    $form['banner']['arts_imgmob'] = [
        '#type' => 'managed_file',
        '#title' => 'Imagen de banner (Mobile)',
        '#required' => FALSE,
        '#upload_location' => file_default_scheme() . '://module/bem_articles',
        '#default_value' => variable_get('arts_imgmob', ''),
        '#upload_validators' => [
            'file_validate_extensions' => array('png jpg jpeg'),
        ],
    ];
    $form['banner']['arts_filter_title'] = [
        '#type' => 'text_format',
        '#title' => 'Mensaje de Filtro',
        '#description' => 'Descripción que aparecerá en espacio para filtrar contenido.',
        '#default_value' => !empty($filter) ? $filter['value'] : '',
        '#rows' => 3,
        '#format' => 'plain_text',
    ];

    // Saved permanent files
    $files['module'] = 'bem_articles';
    $files['files'] = ['arts_imgdesk', 'arts_imgmob'];
    $status = bem_common_fileperm($files);
    if ($status === TRUE) {
        return system_settings_form($form);
    }
}