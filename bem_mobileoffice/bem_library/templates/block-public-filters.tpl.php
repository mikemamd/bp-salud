<?php if( isset($content) && !empty($content) ): ?>
  <div class="row justify-content-center">
    <div class="col-lg-9">
      <div class="row justify-content-center">
        <?php if( isset($content['cont']) && !empty($content['cont']) ): ?>
          <?php if( isset($content['cont']['title']) && !empty($content['cont']['title']) ): ?>
            <div class="col-sm-10 text-center titles"><?php print $content['cont']['title']['value']; ?></div>
          <?php endif; ?>        
          <?php if( isset($content['cont']['desc']) && !empty($content['cont']['desc']) ): ?> 
            <div class="col-sm-12 text-center codigotext1 links-blue">
              <?php print $content['cont']['desc']['value']; ?>
            </div>
          <?php endif; ?>
        <?php endif;?>
        <div class="col-sm-8 text-center pt-4">
          <div class="row justify-content-center">
            <div class="col-10 col-sm-6 my-1">
              <form class="form">
                <select class="my-select mr-sm-2" id="inlineFormCustomSelect">
                  <?php foreach($content['cont'] as $tid => $opt): ?>
                    <option <?php print $opt['class']; ?> value="<?php print $tid; ?>" ><?php print $opt['name']; ?></option>
                  <?php endforeach; ?>
                </select>
              </form>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
<?php endif; ?>