<?php

/**
 * @file
 * default values.
 */

/**
 * Function to defines default values.
 */
function _sharebar_buttons_def() {
  $a = array();

  $a['linkedin'] = new stdClass();
  $a['linkedin']->machine_name = 'linkedin';
  $a['linkedin']->name = 'linkedin';
  $a['linkedin']->big_button = '<script src="//platform.linkedin.com/in.js" type="text/javascript">lang: en_US</script><script type="IN/Share" data-url="[url]" data-counter="top"></script>';
  $a['linkedin']->small_button = '<script src="//platform.linkedin.com/in.js" type="text/javascript">lang: en_US</script><script type="IN/Share" data-url="[url]" data-counter="right"></script>';
  $a['linkedin']->enabled = 1;
  $a['linkedin']->weight = 0;

  $a['googleplus'] = new stdClass();
  $a['googleplus']->machine_name = 'googleplus';
  $a['googleplus']->name = 'googleplus';
  $a['googleplus']->big_button = '<!-- Place this tag where you want the +1 button to render. --><div class="g-plusone" data-size="tall" data-href="[url]"></div><!-- Place this tag after the last +1 button tag. --><script type="text/javascript">(function() {var po = document.createElement(\'script\'); po.type = \'text/javascript\'; po.async = true;po.src = \'https://apis.google.com/js/plusone.js\';var s = document.getElementsByTagName(\'script\')[0]; s.parentNode.insertBefore(po, s);})();</script>';
  $a['googleplus']->small_button = '<!-- Place this tag where you want the +1 button to render. --><div class="g-plusone" data-href="[url]"></div><!-- Place this tag after the last +1 button tag. --><script type="text/javascript">(function() {var po = document.createElement(\'script\'); po.type = \'text/javascript\'; po.async = true;po.src = \'https://apis.google.com/js/plusone.js\';var s = document.getElementsByTagName(\'script\')[0]; s.parentNode.insertBefore(po, s);})();</script>';
  $a['googleplus']->enabled = 1;
  $a['googleplus']->weight = 1;

  $a['twitter'] = new stdClass();
  $a['twitter']->machine_name = 'twitter';
  $a['twitter']->name = 'twitter';
  $a['twitter']->big_button = '<a href="http://twitter.com/share" class="twitter-share-button" data-url="[url]"data-count="vertical" data-via="[twitter]">Tweet</a><script type="text/javascript" src="http://platform.twitter.com/widgets.js"></script>';
  $a['twitter']->small_button = '<a href="http://twitter.com/share" class="twitter-share-button" data-url="[url]" data-count="horizontal" data-via="[twitter]">Tweet</a><script type="text/javascript" src="http://platform.twitter.com/widgets.js"></script>';
  $a['twitter']->enabled = 1;
  $a['twitter']->weight = 2;

  $a['facebook'] = new stdClass();
  $a['facebook']->machine_name = 'facebook';
  $a['facebook']->name = 'facebook';
  $a['facebook']->big_button = '<div id="fb-root"></div> <script>(function(d, s, id) { var js, fjs = d.getElementsByTagName(s)[0]; if (d.getElementById(id)) return; js = d.createElement(s); js.id = id; js.src = "//connect.facebook.net/en_US/all.js#xfbml=1"; fjs.parentNode.insertBefore(js, fjs); }(document, \'script\', \'facebook-jssdk\'));</script> <html xmlns:fb="http://ogp.me/ns/fb#"> <fb:like href="[url]" send="true" layout="box_count" width="450" show_faces="true"></fb:like>';
  $a['facebook']->small_button = '<div id="fb-root"></div> <script>(function(d, s, id) { var js, fjs = d.getElementsByTagName(s)[0]; if (d.getElementById(id)) return; js = d.createElement(s); js.id = id; js.src = "//connect.facebook.net/en_US/all.js#xfbml=1"; fjs.parentNode.insertBefore(js, fjs); }(document, \'script\', \'facebook-jssdk\'));</script> <html xmlns:fb="http://ogp.me/ns/fb#"> <fb:like href="[url]" send="true" layout="button_count" width="450" show_faces="true"></fb:like>';
  $a['facebook']->enabled = 1;
  $a['facebook']->weight = 3;

  $a['digg'] = new stdClass();
  $a['digg']->machine_name = 'digg';
  $a['digg']->name = 'digg';
  $a['digg']->big_button = '<script type="text/javascript">(function() { var s = document.createElement(\'SCRIPT\'), s1 = document.getElementsByTagName(\'SCRIPT\')[0]; s.type = \'text/javascript\'; s.async = true; s.src = \'http://widgets.digg.com/buttons.js\'; s1.parentNode.insertBefore(s, s1); })(); </script><a class="DiggThisButton DiggMedium"></a>';
  $a['digg']->small_button = '<script type="text/javascript">(function() { var s = document.createElement(\'SCRIPT\'), s1 = document.getElementsByTagName(\'SCRIPT\')[0]; s.type = \'text/javascript\'; s.async = true; s.src = \'http://widgets.digg.com/buttons.js\'; s1.parentNode.insertBefore(s, s1); })(); </script><a class="DiggThisButton DiggCompact"></a>';
  $a['digg']->enabled = 1;
  $a['digg']->weight = 4;

  $a['stumbleupon'] = new stdClass();
  $a['stumbleupon']->machine_name = 'stumbleupon';
  $a['stumbleupon']->name = 'stumbleupon';
  $a['stumbleupon']->big_button = '<script src="http://www.stumbleupon.com/hostedbadge.php?s=5"></script>';
  $a['stumbleupon']->small_button = '<script src="http://www.stumbleupon.com/hostedbadge.php?s=2"></script>';
  $a['stumbleupon']->enabled = 1;
  $a['stumbleupon']->weight = 5;

  $a['dzone'] = new stdClass();
  $a['dzone']->machine_name = 'dzone';
  $a['dzone']->name = 'dzone';
  $a['dzone']->big_button = '<script language="javascript" src="http://widgets.dzone.com/links/widgets/zoneit.js"></script>';
  $a['dzone']->small_button = '<script language="javascript" src="http://widgets.dzone.com/links/widgets/zoneit.js"></script>';
  $a['dzone']->enabled = 1;
  $a['dzone']->weight = 6;

  $a['reddit'] = new stdClass();
  $a['reddit']->machine_name = 'reddit';
  $a['reddit']->name = 'reddit';
  $a['reddit']->big_button = '<script type="text/javascript" src="http://reddit.com/static/button/button2.js"></script>';
  $a['reddit']->small_button = '<script type="text/javascript" src="http://reddit.com/static/button/button1.js"></script>';
  $a['reddit']->enabled = 1;
  $a['reddit']->weight = 7;

  $a['designfloat'] = new stdClass();
  $a['designfloat']->machine_name = 'designfloat';
  $a['designfloat']->name = 'designfloat';
  $a['designfloat']->big_button = '<script type="text/javascript">submit_url = \'[url]\';</script><script type="text/javascript" src="http://www.designfloat.com/evb2/button.php"></script>';
  $a['designfloat']->small_button = '<script type="text/javascript">submit_url = \'[url]\';</script><script type="text/javascript" src="http://www.designfloat.com/evb/button.php"></script>';
  $a['designfloat']->enabled = 1;
  $a['designfloat']->weight = 8;

  $a['email'] = new stdClass();
  $a['email']->machine_name = 'email';
  $a['email']->name = 'email';
  $a['email']->big_button = '<a href="mailto:?subject=[url]" class="sharebar-button email">Email</a>';
  $a['email']->small_button = '<a href="mailto:?subject=[url]" class="sharebar-button email">Email</a>';
  $a['email']->enabled = 1;
  $a['email']->weight = 9;

  return serialize($a);
}
