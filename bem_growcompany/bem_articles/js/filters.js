(function($) {
  Drupal.behaviors.bem_articles = {
    attach : function(context) {
      "use strict";

      // Base
      var $base = Drupal.settings.articles.base,
          $items_limit = Drupal.settings.articles.items_limit,
          $pages = 0,
          $max_pages = Drupal.settings.articles.max_pages;

      (function (angular) {

        // Controller
        angular.module("myApp").controller("articlesCtr", function (myService, $scope, $rootScope, $location) {

          // Estado inicial
          // Validar si existen filtros y aplicarlos
          // Se setean las variables apartir del estado de filtros
          var $state = $isFilters(Drupal.settings.articles.filter, $location);
          // Inicializar contenido de articulos
          myService.async($base, $state.content).then(function (results) {
            $rootScope.articles = results.data;
            $buildPager($rootScope, results.pages);
          });

          // Visibilidad inicial Articulo destacado
          $scope.IsVisible = $state.feature_visible;

          // Visibilidad inicial Articulo(s) no encontrados
          $scope.NotFoundArticles = false;

          angular.element("[name=\"category\"], [name=\"type\"]").click(function(){
            myService.async($base, $selectedValues()).then(function (results) {
              $rootScope.articles = results.data;
              $buildPager($rootScope, results.pages);
            });
          });


          angular.element("a.link_flt").click(function(){
              if ($(".check-filter1-" + $(this).data('tid')).attr("checked") === "checked") {
                $(".check-filter1-" + $(this).data('tid')).attr("checked", false);
              } 
              else {
                $(".check-filter1-" + $(this).data('tid')).attr("checked", true);
              } // end if
              myService.async($base, $selectedValues()).then(function (results) {
                $rootScope.articles = results.data;
                $buildPager($rootScope, results.pages);
              });
              return false;
          });

          angular.element("a.link_type").click(function(){
              if ($(".check-filter1-" + $(this).data('tid')).attr("checked") === "checked") {
                $(".check-filter1-" + $(this).data('tid')).attr("checked", false);
              } 
              else {
                $(".check-filter1-" + $(this).data('tid')).attr("checked", true);
              } // end if
              myService.async($base, $selectedValues()).then(function (results) {
                $rootScope.articles = results.data;
                $buildPager($rootScope, results.pages);
              });
              return false;
          });

          // Filtro de articulos
          angular.element('[name="subcategory"], .envio-noticias, #envio-noticias').click(function () {
            // Visisblilidad de Articulo destacado
            var $arr = $selectedValues();
            if ( ($arr[0].category.length > 0) ||  ($arr[0].subcategory.length > 0)
                || ($arr[0].type.length > 0) || ($arr[0].search.length > 0)) {
              $scope.IsVisible = false;
            } else {
              $scope.IsVisible = true;
            }

            myService.async($base, $selectedValues()).then(function (results) {
              $rootScope.articles = results.data;
              $buildPager($rootScope, results.pages);
            });
          });

          // Eliminar Filtros
          $scope.cleanFilters = function() {
            myService.async($base, []).then(function (results) {
              $scope.IsVisible = true;
              $rootScope.articles = results.data;
              $buildPager($rootScope, results.pages);
            });
          };

          // Busqueda
          // Click on Search Trigger
          angular.element("[name=\"artsearch\"]").on("keypress", function (e) {
            var keycode = e.keyCode || e.which;
            if (keycode == 13) {
              // Visisblilidad de Articulo destacado
              $scope.IsVisible = false;
              var $arr = $selectedValues();
              if (($arr[0].search.length <= 0)) {
                $scope.IsVisible = true;
              } // end if

              myService.async($base, $selectedValues()).then(function (results) {

                if ($.isEmptyObject(results.data) === true) {
                  $scope.NotFoundArticles = true;
                } else {
                  $scope.NotFoundArticles = false;
                } // end if

                $rootScope.articles = results.data;
                $buildPager($rootScope, results.pages);
              });

              return false;
            }

          });

          // Submit
          angular.element(".form-filter").submit(function(e){
            e.preventDefault();
            return false;
          });

          // Social PopUp
          $scope.socialPopUp = function (e) {
            $(e.target).next().toggleClass("open-menu");
          };

        });

        // dsPagerCtr
        angular.module("myApp").controller("dsPagerCtr", function (myService, $scope, $rootScope,$window) {

          $scope.page_limit = 3;

          // Pagina siguiente
          $rootScope.paginaSiguiente = function () {
            var $last = (angular.element($("#pagination li:last-child")).data("page") + 1);
            $rootScope.prev_show = true;
            $rootScope.next_show = true;
            $rootScope.data = [];
            var $increment = 0;
            var $active = 0;
            for (var i = 0; i <= 2; i++) {
              $increment = (i + $last);
              if ($increment < $pages) {
                $active = 0;
                if (i === 0) {
                  $active = 1;
                }
                $rootScope.data.push({
                  page : $increment,
                  active: $active
                });
              } // end if
            }

            if ($increment >= ($pages - 1)) {
              $rootScope.next_show = false;
            }

            myService.async($base, $selectedValues($last * $items_limit)).then(function (results) {
              $rootScope.articles = [];
              $rootScope.articles = results.data;
              $('html, body').animate({
                scrollTop: $("#carousel-custom").offset().top
              }, 0);
            });
          };

          // Pagina anterior
          $rootScope.paginaAnterior = function() {
            var $first = (angular.element($("#pagination li:first-child")).data("page") - 1);
            $rootScope.prev_show = true;
            $rootScope.next_show = true;
            if ($first <= 2) {
              $rootScope.prev_show = false;
            }

            $rootScope.data = [];
            var $active = 0;
            for (var i = 2; i >= 0; i--) {
              $active = 0;
              if (i === 2) {
                $active = 1;
              }
              $rootScope.data.push({
                    page : ($first - i),
                    active: $active
                  });
            }
            var $item_l = $getActivePage() * $items_limit;
            if($item_l==0){
              $item_l = 1;
            }
            myService.async($base, $selectedValues($item_l)).then(function (results) {
              $rootScope.articles = [];
              $rootScope.articles = results.data;
              $('html, body').animate({
                scrollTop: $("#carousel-custom").offset().top
              }, 0);
            });

          };

          // Cargar items adicionales
          $scope.cargarNoticias = function($item) {
            if($item==0){
              $item = 0.11;
            }
            angular.element($("#pagination a")).removeClass("active");
            angular.element($("#pagination a")).each(function () {
              if ($(this).data("page") === $item) {
                angular.element($(this)).addClass("active");
              }
            });

            myService.async($base, $selectedValues($item * $items_limit)).then(function (results) {
              $rootScope.articles = [];
              $rootScope.articles = results.data;
              $('html, body').animate({
                scrollTop: $("#carousel-custom").offset().top
              }, 0);
            });

            return false;
          };

        });

        var $getActivePage = function() {
          var $page = 0;
          angular.element($("#pagination a")).each(function () {
            if ($(this).hasClass("active")) {
              $page = ($(this).data("page") - 3);
            }
          });
          return $page;
        };

        var $buildPager = function($rootScope, $results_pages) {
          // Paginador
          $rootScope.data = [];
          $rootScope.prev_show = false;
          $rootScope.next_show = false;
          $max_pages = 3;

          // Validando resultados de las páginas
          if ($results_pages < 3 ) {
            $max_pages = $results_pages;
          }

          // Validando si existe hashtag
          var hash = window.location.hash.substr(1);
          var $y = hash.split("=")[1];
          var $is_hash = false;
          if (typeof $y !== "undefined") {
            $is_hash = (parseInt($y) / 9);
          }

          // Buscando item seleccionado en página
          var $active = 0;
          for (var i=0; i < $max_pages; i++) {
            $active = 0;
            if ($is_hash === false && i === 0) {
              $active = 1;
            } else if ($is_hash !== false && $is_hash === i) {
              $active = 1;
            } // end if

            $rootScope.data.push({
              page : i,
              active: $active
            });
          } // end for

          if ($results_pages > 3) {
            $rootScope.next_show = true;
            angular.element($("#pagination a")).removeClass("active");
            angular.element($("#pagination a:eq(0)")).addClass("active");
          }

          // Numero de paginas del paginado
          $pages = $results_pages;
        };

      })(window.angular);

      // Valores seleccionados
      var $selectedValues = function($offset) {
        $offset = Math.round($offset);
        var tidsCategory = [],
            tidsSubcategory = [],
            tidsType = [],
            data = [];

        var inputSearch = $("#search").val();

        // Category
        $('input[name="category"]:checked').each(function(){
          tidsCategory.push(this.value);
        });
        // Subcategory
        $('input[name="subcategory"]:checked').each(function(){
          tidsSubcategory.push(this.value);
        });
        // Type
        $('input[name="type"]:checked').each(function(){
          tidsType.push(this.value);
        });
        if ($offset === "" || $offset === "undefined") {
          $offset = 1;
        } // end if

        // if unedined $offset
        if (typeof $offset === "undefined") {
          $offset = 1;
        }
        // Añadiendo almoadilla en url
        window.location.hash = "#segment=" + $offset;

        data.push({
          category: tidsCategory,
          subcategory: tidsSubcategory,
          type: tidsType,
          search: inputSearch,
          offset: $offset
        });

        return data;
      };

      // Filtros
      var $isFilters = function($filter, $location) {

        var $prop = [];
        $prop.feature_visible = true;
        $prop.content = [];
        if ($filter !== "") {
          var $category_data = [];
          $prop.feature_visible = false;
          $category_data.push($filter);
          $prop.content.push({ category : $category_data});
        }

        $prop.content.push({ offset : $location.hash().split("=")[1] });
        return $prop;
      };

    }
  };
})(jQuery);

