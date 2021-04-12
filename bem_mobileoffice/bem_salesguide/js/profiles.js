(function($) {
  Drupal.behaviors.bem_salesguide = {
    attach : function(context) {
      'use strict';

      // Default state
      var flag = 1;
      $('.profile-button').each(function(){
        if ( flag == 1 ) {
          $(this).addClass('cta-blue');
          $(this).removeClass('cta-orange');            
        }
        flag++;
      });


      // Click on Profiles button
      $('.profile-button').click(function() { 
        var pos = $(this).attr("data-pos");
        
        // Remove active class to all buttons
        $('.profile-button').each(function(){
          if ( $(this).hasClass('cta-blue') ) {
            $(this).addClass('cta-orange');
            $(this).removeClass('cta-blue');            
          }
        });

        // Add class to current button
        $(this).addClass('cta-blue');

        // Change content to carousel from [owl-carousel API]
        var carousel = $(".owl-carousel");
        carousel.owlCarousel();
        carousel.trigger("to.owl.carousel", [pos]);
      });


    }
  };
})(jQuery);
