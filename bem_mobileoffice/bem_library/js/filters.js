(function($) {
  Drupal.behaviors.bem_library = {
    attach : function(context) {
      'use strict';
      (function (angular) {
        // Base
        var $base = Drupal.settings.library.base,
            $filter = Drupal.settings.library.filter;

        // Controller
        angular.module("myApp").controller('libraryCtr', function (myService, $scope, $location) {
          var filterCountry = $('[id="countryfilter"]'),
              filterCatmob = $('[id="sel-docs"]'),
              
              data = [],
              params = [];

          // Load default data
          params.push({
            country: $filter,
            type: 0,
          });

          $scope.mobtabs = '';
          $scope.items = [];
          $scope.privtabs = [];
          $scope.isVisible = false;
          $scope.tabActive = 0;
          $scope.tabPrivActive = 0;

          myService.async($base, params).then(function (results) {
            $scope.library = results.datapub;
            $scope.tabs = results.tabspub;

            if ($scope.library.length !== 0) {
              $scope.isVisible = true;
            } // end if

            // Publicos
            $scope.selectedItem = results.mobtabspub[0];
            $scope.items = results.mobtabspub;
            $scope.privlibrary = results.datapriv;
            $scope.tabActive = $scope.tabs[0].nid;

            // Privados
            $scope.privtabs = results.tabspriv;
            $scope.tabPrivActive = results.tabspriv[0][0].nid;
            $scope.privmobtabs = results.mobtabsprv;
            $scope.privtabsslected = results.mobtabsprv[0];

          });

          // Change select of country
          filterCountry.change(function(){
            params = getdata();

            myService.async($base, params).then(function (results) {
              $scope.isVisible = true;
              // PUBLIC DOCUMENTS

              $scope.library = results.datapub;
              $scope.tabs = results.tabspub;
              $scope.selectedItem = results.mobtabspub[0];
              $scope.items = results.mobtabspub;

              // PRIV DOCUMENTS
              $scope.privlibrary = results.datapriv;
              $scope.privtabs = results.tabspriv;
              $scope.privmobtabs = results.mobtabsprv;
              $scope.privtabsslected = results.mobtabsprv[0];

              // DEFAULT ACTIVE TABS
              $scope.tabActive = results.mobtabspub[0]['nid'];
              $scope.tabPrivActive = results.mobtabsprv[0]['nid'];
            });

          });

          // Change select of Categories Mobile
          filterCatmob.change(function(){
            var ctrySelect = $(this).val();
            params = getdata(ctrySelect);
            // Conect with service to retrive content
            myService.async($base, params).then(function (results) {
              $scope.library = results.datapub;
              $scope.tabs = results.tabspub;
              $scope.privlibrary = results.datapriv;
              $scope.privtabs = results.tabspriv;
            });              

          });

          // Click on Categories Desktop
          $scope.tabclick = function(element) {

            params = getdata(element);
            // Conect with service to retrive content
            myService.async($base, params).then(function (results) {
              $scope.library = results.datapub;
              $scope.tabs = results.tabspub;
            });
            
            $scope.tabActive = element;
          }              

          // Click on Categories Desktop
          $scope.privclick = function(element) {

            params = getdata(element);
            // Conect with service to retrive content
            myService.async($base, params).then(function (results) {
              $scope.privlibrary = results.datapriv;
              $scope.privtabs = results.tabspriv;
            });

            $scope.tabPrivActive = element;
          }   


          // Retrive values on filters
          function getdata(catSelect) {
            var tidCountry = '0',
                tidType = '0',
                data = [];

            $( "#countryfilter option:selected" ).each(function() {
              tidCountry = $(this).val();
            });

            tidType = $('[id="dctype"]').attr('data-id'),

            data.push({
              category: catSelect,
              country: tidCountry,
              type: tidType,
            });

            return data;
          };


        });


      })(window.angular);

    }
  };
})(jQuery);
