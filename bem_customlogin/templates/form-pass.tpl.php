    <div class="form-group">
        <label for="email">Introduce tu correo electrónico*</label>
        <?php print render($form["name"]); ?>
    </div>

    <div class="row text-center">
        <div class="col-md-12 pb-3 text-left small-text">
            *Campos obligatorios
        </div>

        <div class="col-md-12 py-3">
            <button type="submit" class="btn btn-primary btn-orange">Continuar</button>
            <?php print render($form["submit"]); ?>
        </div>

    </div>

<?php print drupal_render_children($form); ?>