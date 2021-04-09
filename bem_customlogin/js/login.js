(function($) {
  Drupal.behaviors.bem_customlogin = {
    attach : function(context) {
      $(document).on('ready', function(){
        $('input#bem_customlogin_user_login').get(0).type = '';
      });

    }
  };
})(jQuery);
