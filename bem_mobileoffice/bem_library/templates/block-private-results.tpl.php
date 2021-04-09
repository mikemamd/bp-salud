<?php if( isset($content['info']) && !empty($content['info']) ): ?>
  <!-- DOC PRIVADOS -->
  <section class="seccion pb-5">
    <div class="container" id="dcprivtype" data-id="1" ng-app="myApp" ng-controller="libraryPriv">
      <!-- BLOCK INFO -->
      <div class="row justify-content-center pt-5">
        <div class="col-lg-9">
          <div class="row justify-content-center">
            <div class="col-sm-10 text-center titles">
              <?php print $content['info']['title']['value']; ?>
            </div>
            <div class="col-sm-12 text-center codigotext1 links-blue">
              <?php print $content['info']['title']['value']; ?>
            </div>
          </div>
        </div>
      </div>
      <!-- END BLOCK INFO -->

      <!-- TABS MOBILE -->
      <div class="col-sm-12 text-center pt-4 d-sm-none">
        <div class="row justify-content-center">
          <div class="col my-1">
            <form class="form">
              <select id="sel-docs-1" class="my-select-2 mr-sm-2" id="inlineFormCustomSelect">
                <div ng-repeat="mobcategories in tabs" >
                  <div class="col" ng-repeat="mobcat in mobcategories">
                    <option value="{{ mobcat.nid }}">{{ mobcat.name }}</option>
                  </div>
                </div>
              </select>
            </form>
          </div>
        </div>
      </div>
      <!-- END TABS MOBILE -->
      
      <!-- STRUCTURE DROPS -->
      <div class="row justify-content-center pt-5 ">
        <div class="col-md-12 justify-content-center">
         
          <!-- TABS DESKTOP -->
          <ul id="docs-tabs-1" class="justify-content-center nav docs-tabs text-center pb-4 d-none d-lg-flex d-sm-none" ng-repeat="categories in tabs">
            <div class="col-" ng-repeat="cat in categories"> 
              <li class="orange-tab tabbutton" data-id="{{ cat.nid }}" data-toggle="tab" ng-click="tabclick(cat.nid)">
                <a href="" data-id="{{ cat.nid }}" id="pub-docs" >{{ cat.name }}</a>
              </li>
            </div>
          </ul>
          <!-- END TABS DESKTOP -->

          <!-- TABS CONTENT -->
          <div ng-repeat="(subcat, rows) in library">
            <div class="tab-content" id="TabContent-{{ rows.nid }}" >
              <div class="tab-pane fade show active" id="cont-{{ rows.nid }}" role="tabpanel" aria-labelledby="home-tab">
                <div id="accordion">
                  <!-- DPROP DOWNN -->
                  <div>
                    <div class="panel-heading" id="heading-priv-{{ rows.delta }}">
                      <div class="panel-heading" id="heading-priv-{{ rows.delta }}" data-toggle="collapse" data-target="#collapse-priv-{{ rows.delta }}" aria-expanded="true" aria-controls="collapse-priv-{{ rows.delta }}">
                        {{ subcat }}
                      </div>
                    </div>
                    <div id="collapse-priv-{{ rows.delta }}" class="collapse" aria-labelledby="heading-priv-{{ rows.delta }}" data-parent="#accordion">
                      <div class="card-body background-blue col-12 pt-4 pb-5">
                        <div class="row ">
                          <div class="col-sm text-center h-blue pb-3">
                            Te pueden interesar los siguientes documentos
                          </div>
                        </div>
                        <!-- DOCS -->
                        <div class="row justify-content-around" ng-repeat="row in rows.docs">
                          <div class="col-sm" ng-repeat="(delta, doc) in row">
                            <div class="row int-d justify-content-center mx-auto mt-4">
                              <div class="col-8">
                                {{ doc.name }}
                              </div>
                              <div class="col-2 align-self-center">
                                <a href="{{ doc.f_one }}" target="_blank">{{ doc.a_one }}</a>
                                <a href="{{ doc.f_two }}" target="_blank">{{ doc.a_two }}</a>
                              </div>
                            </div>
                          </div>
                        </div>
                        <!-- DOCS -->
                      </div>
                    </div>
                  </div>
                  <!-- END DPROP DOWNN -->
                </div>
              </div>
            </div>
          <!-- END TABS CONTENT -->
        </div>
      </div>   
      <!-- STRUCTURE DROPS -->
    </div>
  </section>
<?php endif; ?>    

