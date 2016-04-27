
(function ($) {
    Drupal.behaviors.jqueryColorpicker = {
    attach: function() {
      var ids = ["edit-sharebar-bar-background","edit-sharebar-bar-border"];
      $.each(ids, function() {
        var id = this;
        $("#"+this).ColorPicker({
          onSubmit: function(hsb, hex, rgb, el) {
            $(el).val(hex);
            $(el).ColorPickerHide();
          },
          onBeforeShow: function () {
            $(this).ColorPickerSetColor(this.value);
          },
          onChange: function(hsb, hex, rgb, el) {
            $("#"+id).val(hex);
          }
        });
      });
    }
}
})(jQuery)