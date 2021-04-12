<?php global $base_url; ?>
<?php $theme_path = $base_url . '/' . drupal_get_path('theme', 'bptheme') . '/'; ?>

<!-- Buscador -->
<form class="form-inline my-2 my-lg-0" action="<?php print $path['action']; ?>" method="get">
    <input class="form-control search-input" name="bemsearch" type="Buscar" placeholder="Buscar" aria-label="Buscar">
    <button class="btn my-2 my-sm-0 search-btn" type="submit">
        <img src="<?php print $theme_path; ?>img/icons/search.svg" alt="">
    </button>
</form>
<!--Fin Buscador -->
