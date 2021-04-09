    <div class="form-group mb-4">
        <?php print render($form["bem_customlogin_user_login"]); ?>
    </div>
    <div class="form-group">
        <?php print render($form["bem_customlogin_password_login"]);?>
        <span id="show_password" class="field-icon" ng-click="hideShowPassword()"></span>
    </div>
    <div class="row text-center">
        <div class="col-md-12 pb-3 text-left small-text">
            <a class="classic-link" href="/user/password"><?php print variable_get('login_pass',''); ?></a>
        </div>

        <div class="col-md-6 py-3">
            <?php print render($form["bem_customlogin_redirect_private_nodeid"]);?>
            <?php print render($form["submit"]); ?>
        </div>
        <div class="col-md-6 py-3">
            <a href="/user/registro-agentes" class="btn btn-primary btn-orange text-light d-md-block d-none"><?php print t("Registrarse"); ?></a>
            <a class="classic-link d-block d-md-none" href="/user/registro-agentes"><?php print t("Registrarse"); ?></a>
        </div>

        <div class="col-md-12 py-3 text-center small-text">
            <?php print variable_get('login_bajo',''); ?>
        </div>
    </div>

<?php print drupal_render_children($form); ?>