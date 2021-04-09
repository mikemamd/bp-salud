<?php if( isset($content) && !empty($content) ): ?> 
  <!-- BANNER GUÍA DE VENTAS -->
  <div class="hero">
    <img class="d-lg-block d-sm-none d-none w-100" src="<?php print $content['img_d']; ?>" alt="">
    <img class="d-block d-lg-none w-100" src="<?php print $content['img_m']; ?>" alt="">
    <?php if( isset($content['title']) && !empty($content['title']) ): ?>
      <div class="container-descripction-hero">
        <h1 class="display-4 text-center hero-titles"><?php print $content['title']['value']; ?></h1>
        <p class="lead text-center hero-stitles m-0"><?php print $content['body']['value']; ?></p>
      </div>
    <?php endif; ?>
  </div>
  <!-- FIN BANNER -->
<?php endif; ?>

  <style type="text/css">
    h1.title-section {
      color: #fff !important;
    }
  </style>


