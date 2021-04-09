
<section id="login" class="px-md-4 pt-md-4 p-2 pb-0 form-container">
    <div class="container-fluid" ng-app="myApp">
        <div class="row justify-content-md-center">
            <div class="col-12 col-md-6 msn-login py-4">
                <div class="col-md-12 px-0 mx-auto text-center">
                    <div class="pb-4 pt-0 pt-md-5 title">
                        <?php print $content['msn_titulo']; ?>
                    </div>
                    <div class="pb-3 px-sm-0 col-12 col-md-10 mx-auto">
                        <?php print $content['msn_subtitulo']; ?>
                    </div>
                    <div class="pb-4 video-login">
                        <?php print $content['msn_descr']; ?>
                    </div>
                </div>
            </div>
            <div class="col-12 col-md-6 py-4">
                <div class="col-md-12 mx-auto text-center">
                    <div class="pb-2">
                        <img src="<?php print $content['theme_path']; ?>/creador-mensajes/images/icons/log_in_icon.svg">
                    </div>

                    <div class="pb-5 title">
                        <?php print $content['login_inicio_sesion']; ?>
                    </div>

                    <div class="pb-3 login-subtitulo">
                        <?php print $content['login_subtitulo']; ?>
                    </div>

                    <?php if($content['login_descr']):?>
                    <?php print '<div class="px-0 pb-4 col-md-7 mx-auto small-text">'.$content['login_descr'].'</div>';?>
                    <?php endif;?>
                </div>

                <div class="col-12 col-md-10 col-lg-6 mx-auto">
                    <?php print drupal_render($content['form']); ?>
                </div>
            </div>
        </div>
    </div>
</section>
