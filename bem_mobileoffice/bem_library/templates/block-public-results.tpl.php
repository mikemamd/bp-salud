<div ng-app="myApp" ng-controller="libraryCtr">
  <section class="seccion">
    <div class="container" id="dctype" data-id="0" >
      <!-- FILTERS -->
      <?php if( isset($content['filter']) && !empty($content['filter']) ): ?>
        <div class="row justify-content-center">
          <div class="col-lg-9">
            <div class="row justify-content-center">
              <?php if( isset($content['info']['filter_t']) && !empty($content['info']['filter_t']) ): ?>
                <div class="col-sm-10 text-center titles"><?php print $content['info']['filter_t']['value']; ?></div>
              <?php endif; ?>
              <?php if( isset($content['info']['filter_d']) && !empty($content['info']['filter_d']) ): ?>
                <div class="col-sm-12 text-center codigotext1 links-blue">
                  <?php print $content['info']['filter_d']['value']; ?>
                </div>
              <?php endif; ?>
              <div class="col-sm-8 text-center pt-4">
                <div class="row justify-content-center">
                  <div class="col-10 col-sm-6 my-1">
                    <form class="form">
                      <select class="my-select mr-sm-2" id="countryfilter">
                         <option value="" disabled selected>País</option>
                        <?php foreach($content['filter'] as $tid => $opt): ?>
                          <option <?php print $opt['class']; ?> value="<?php print $tid; ?>"><?php print $opt['name']; ?></option>
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
      <!-- FILTERS -->
        
      <!-- DOCUMENTOS DE INTERES -->
      <div class="row justify-content-center pt-5" >
        <div class="col-lg-9">
          <div class="row justify-content-center">
            <?php if( isset($content['info']['result_t']) && !empty($content['info']['result_t']) ): ?>
              <div class="col-sm-10 text-center titles"><?php print $content['info']['result_t']['value']; ?></div>
            <?php endif; ?>
            <?php if( isset($content['info']['result_d']) && !empty($content['info']['result_d']) ): ?>
              <div class="col-sm-12 text-center codigotext1 links-blue">
                <?php print $content['info']['result_d']['value']; ?>
              </div>
            <?php endif; ?>
          </div>
        </div>
      </div>
      <!-- TABS MOBILE -->
      <div class="col-sm-12 text-center pt-4 d-sm-none">
        <div class="row justify-content-center">
          <div class="col my-1">
            <form class="form">

              <select id="sel-docs" class="my-select-2 mr-sm-2" 
              ng-show="isVisible"
              ng-model="selectedItem"
              ng-options="item.name for item in items track by item.nid"></select>

            </form>
          </div>
        </div>
      </div>
      <!-- END TABS MOBILE -->
      <!-- STRUCTURE DROPS -->

      <div class="row justify-content-center pt-5">
       <!-- <div class="col-md-12 ng-url"> -->
        <div class="col-md-12">
          <!-- TABS DESKTOP -->
          <ul id="docs-tabs" class="justify-content-around nav docs-tabs text-center pb-4 d-none d-lg-flex d-sm-none" ng-repeat="categories in tabs">
            <div class="col-" ng-repeat="cat in categories">
              <li class="orange-tab tabbutton" data-id="{{ cat.nid }}" data-toggle="tab" 
                  ng-click="tabclick(cat.nid)" ng-class="{'active': cat.nid == tabActive }" >
                <a href="" data-id="{{ cat.nid }}" id="pub-docs" >{{ cat.name }}</a>
              </li>
            </div>
          </ul>
          <!-- END TABS DESKTOP -->
          <!-- DROPDOWNS -->
          <div ng-repeat="(subcat, rows) in library">
            <div class="tab-content" id="TabContent-{{ rows.nid }}"  >
              <div class="tab-pane fade show active" id="cont-{{ rows.nid }}" role="tabpanel" aria-labelledby="home-tab">
                <!-- ACCORDION ITEM -->                  
                <div id="accordion">
                  <div>
                    <div class="panel-heading" id="heading-{{ rows.delta }}">    
                      <div class="panel-heading" id="heading-{{ rows.delta }}" data-toggle="collapse" data-target="#collapse-{{ rows.delta }}" aria-expanded="true" aria-controls="collapse-{{ rows.delta }}">
                          {{ subcat }}
                      </div>    
                    </div>
                    <div id="collapse-{{ rows.delta }}" class="collapse" aria-labelledby="heading-{{ rows.delta }}" data-parent="#accordion">
                      <div class="card-body background-blue col-12 pt-4 pb-5">
                        <div class="row ">
                          <div class="col-sm text-center h-blue pb-3">
                            {{ rows.intro }} 
                          </div>
                        </div>
                        <!-- DOCUMENTS -->
                        <div class="row justify-content-around" ng-repeat="row in rows.docs">
                          <div class="col-sm" ng-repeat="(delta, doc) in row">
                            <div class="row int-d justify-content-center mx-auto mt-4">
                              <div class="col-8" ng-bind-html="doc.name | sanitize">
                              </div>
                              <div class="col-2 align-self-center">
                                <a class="classic-link" href="{{ doc.f_one }}" target="_blank" ng-show="(doc.a_one != '--')">{{ doc.a_one }}</a>
                                <a class="classic-link" href="{{ doc.f_two }}" target="_blank" ng-show="(doc.a_two != '--')">{{ doc.a_two }}</a>
                              </div>
                            </div>
                          </div>
                        </div>
                        <!-- END DOCUMENTS -->
                      </div>
                    </div>
                  </div>
                </div>
                <!-- END ACCORDION ITEM -->
              </div>
            </div>
          </div>
          <!-- END DROPDOWNS -->
        </div>
      </div>
      <!-- END STRUCTURE DROPS -->
    </div>
  </section>




  <!-- DOC PRIVADOS -->
  <section class="seccion pb-5">
    <div class="container" id="dcprivtype" data-id="1" >
      <!-- BLOCK INFO -->
      <div class="row justify-content-center pt-5">
        <div class="col-lg-9">
          <div class="row justify-content-center">
            <?php if( isset($content['infopriv']['title']) && !empty($content['infopriv']['title']) ): ?>
              <div class="col-sm-10 text-center titles">
                <?php print $content['infopriv']['title']['value']; ?>
              </div>
            <?php endif; ?>
            <?php if( isset($content['infopriv']['desc']) && !empty($content['infopriv']['desc']) ): ?>
              <div class="col-sm-12 text-center codigotext1 links-blue">
                <?php print $content['infopriv']['desc']['value']; ?>
              </div>
            <?php endif; ?>
          </div>
        </div>
      </div>
      <!-- END BLOCK INFO -->

      <!-- TABS MOBILE -->
      <div class="col-sm-12 text-center pt-4 d-sm-none">
        <div class="row justify-content-center">
          <div class="col my-1">
            <form class="form">
              <select id="sel-docs-1" class="my-select-2 mr-sm-2" id="inlineFormCustomSelect" 
              ng-show="isVisible"
              ng-model="privtabsslected"
              ng-options="privm.name for privm in privmobtabs track by privm.nid"></select>
            </form>
          </div>
        </div>
      </div>
      <!-- END TABS MOBILE -->
      
      <!-- STRUCTURE DROPS -->
      <div class="row justify-content-center pt-5 ">
        <div class="col-md-12 justify-content-center">
         
          <!-- TABS DESKTOP -->
          <ul id="docs-tabs" class="justify-content-around nav docs-tabs text-center pb-4 d-none d-lg-flex d-sm-none" ng-repeat="categories in privtabs">
            <div class="col-" ng-repeat="cat in categories">
              <li class="orange-tab tabbutton" data-id="{{ cat.nid }}" data-toggle="tab" 
                  ng-click="privclick(cat.nid)" ng-class="{'active': cat.nid == tabPrivActive }" >
                <a href="" data-id="{{ cat.nid }}" id="pub-docs" >{{ cat.name }}</a>
              </li>
            </div>
          </ul>
          <!-- END TABS DESKTOP -->


          <!-- TABS CONTENT -->
          <div ng-repeat="(subcat, rows) in privlibrary">
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
                              <div class="col-8" ng-bind-html="doc.name | sanitize">
                              </div>
                              <div ng-if="rows.type ==='priv'">
                                <div class="col-2 align-self-center" ng-show="(doc.a_one != '--')">
                                  <a class="classic-link" href="{{ doc.f_one }}" target="_blank"><img src="{{ doc.a_one }}"></a>
                                </div>
                              </div>
                              <div ng-if="rows.type ==='pub'">
                                <div class="col-2 align-self-center">
                                  <a class="classic-link" href="{{ doc.f_one }}" target="_blank" ng-show="(doc.a_one != '--')">{{ doc.a_one }}</a>
                                  <a class="classic-link" href="{{ doc.f_two }}" target="_blank" ng-show="(doc.a_two != '--')">{{ doc.a_two }}</a>
                                </div>
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

</div>