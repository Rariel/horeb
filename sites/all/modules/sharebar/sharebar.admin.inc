<?php

/**
 * @file
 * Admin page callbacks for the block module.
 */

/**
 * Theme the administer buttons page.
 *
 * @ingroup themeable
 */
function theme_sharebar_buttons_table($variables = NULL) {

  $data = &drupal_static(__FUNCTION__, NULL);

  if (!isset($data)) {
    if (($cache = cache_get("sharebar_data")) && !empty($cache->data)) {
      $data = $cache->data;
    }
    else {
      $data .= '<div>' . l(t('Add New Button'), 'admin/config/sharebar/add') . '</div>';
      $buttons = unserialize(variable_get('sharebar_buttons', sharebar_buttons_def()));
      if (is_array($buttons) && count($buttons)) {
        usort($buttons, "sharebar_cmp_up");
        foreach ($buttons as $key => $value) {
          $row = array();
          $row[] = array('data' => ($value->enabled ? t('Yes') : t('No')));
          $row[] = array('data' => $value->name);
          $row[] = array('data' => $value->big_button);
          $row[] = array('data' => $value->small_button);
          $row[] = array('data' => $value->weight);
          $row[] = array(
            'data' => l(t('Edit'), 'admin/config/sharebar/edit/' . $value->machine_name) .
            ' | '
            . l(t('Delete'), 'admin/config/sharebar/del/' . $value->machine_name));
          $rows[] = $row;
        }
      }
      if (count($rows)) {
        $header = array(
          t('Enabled'),
          t('Name'),
          t('Big Button'),
          t('Small Button'),
          t('Weight'),
          t('Actions'),
        );
        $data .= theme('table', array('header' => $header, 'rows' => $rows));
      }
      else {
        $data .= '<b>' . t('No data') . '</b>';
      }
      cache_set("sharebar_data", $data);
    }
  }
  return $data;
}

/**
 * Form builder: create buttons.
 */
function sharebar_addbutton($form, &$form_state, $edit = array()) {
  $mname = arg(4);
  $button = new stdClass();
  $button->name = $button->machine_name = $button->big_button = $button->small_button = $button->enabled = $button->weight = '';
  if ($mname) {
    $buttons = unserialize(variable_get('sharebar_buttons', sharebar_buttons_def()));
    if (is_array($buttons) && count($buttons)) {
      $button = $buttons[$mname];
    }
  }
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $button->name,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $button->machine_name,
    '#maxlength' => 21,
    '#machine_name' => array(
      'exists' => 'sharebar_machine_name_load',
    ),
  );
  $form['old_machine_name'] = array(
    '#type' => 'value',
    '#value' => $button->machine_name,
  );
  $form['big_button'] = array(
    '#type' => 'textarea',
    '#title' => t('Big Button'),
    '#default_value' => $button->big_button,
    '#required' => TRUE,
  );
  $form['small_button'] = array(
    '#type' => 'textarea',
    '#title' => t('Small Button'),
    '#default_value' => $button->small_button,
    '#required' => TRUE,
  );
  // Display placeholders.
  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#description' => t('Be very careful while using node specific tokens, 
        as these are available only for nodes, so you might see naked token on 
        non-nodes and can be a reason for breakage:'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node'),
      '#show_restricted' => TRUE,
      '#dialog' => TRUE,
      '#description' => t('x'),
    );
  }

  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => $button->enabled,
  );

  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#delta' => 50,
    '#default_value' => $button->weight,
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;
}

/**
 * Submit handler for hook_addbutton().
 */
function sharebar_addbutton_submit($form, &$form_state) {

  if ($form_state['clicked_button']['#value'] == t('Delete')) {
    $form_state['rebuild'] = TRUE;
    $form_state['confirm_delete'] = TRUE;
    return;
  }

  $buttons = unserialize(variable_get('sharebar_buttons', sharebar_buttons_def()));

  if ($form_state['values']['old_machine_name'] != '' && $form_state['values']['old_machine_name'] != $form_state['values']['machine_name']) {
    unset($buttons[$form_state['values']['old_machine_name']]);
  }

  $buttons[$form_state['values']['machine_name']] = new stdClass();
  $buttons[$form_state['values']['machine_name']]->machine_name = $form_state['values']['machine_name'];
  $buttons[$form_state['values']['machine_name']]->name = $form_state['values']['name'];
  $buttons[$form_state['values']['machine_name']]->big_button = $form_state['values']['big_button'];
  $buttons[$form_state['values']['machine_name']]->small_button = $form_state['values']['small_button'];
  $buttons[$form_state['values']['machine_name']]->enabled = $form_state['values']['enabled'];
  $buttons[$form_state['values']['machine_name']]->weight = $form_state['values']['weight'];

  variable_set('sharebar_buttons', serialize($buttons));

  $form_state['redirect'] = 'admin/config/sharebar/settings';
}

/**
 * Form builder: delete buttons.
 */
function sharebar_button_confirm_delete($form, &$form_state) {
  $mname = arg(4);
  if ($mname) {
    $buttons = unserialize(variable_get('sharebar_buttons', sharebar_buttons_def()));
    if (is_array($buttons) && count($buttons)) {
      $button = $buttons[$mname];
    }
  }

  $form['machine_name'] = array('#type' => 'value', '#value' => $button->machine_name);

  $form['#button'] = $button;
  $form['type'] = array('#type' => 'value', '#value' => 'button');
  $form['name'] = array('#type' => 'value', '#value' => $button->name);

  $form['delete'] = array('#type' => 'value', '#value' => TRUE);
  return confirm_form($form,
    t('Are you sure you want to delete the button %title?',
    array('%title' => $button->name)),
    'admin/config/sharebar/settings',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel'));
}

/**
 * Submit handler for hook_button_confirm_delete().
 */
function sharebar_button_confirm_delete_submit($form, &$form_state) {

  $mname = arg(4);
  if ($form_state['values']['machine_name']) {
    $buttons = unserialize(variable_get('sharebar_buttons', sharebar_buttons_def()));
    if (is_array($buttons) && count($buttons)) {
      unset($buttons[$form_state['values']['machine_name']]);
      variable_set('sharebar_buttons', serialize($buttons));
    }
  }

  drupal_set_message(t('Deleted buttons %name.', array('%name' => $form_state['values']['name'])));
  watchdog('ShareBar', 'Deleted buttons %name.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/config/sharebar/settings';
  cache_clear_all();
  // return;
}

/**
 * Callback to load existing machine name.
 */
function sharebar_machine_name_load($name) {
  $buttons = unserialize(variable_get('sharebar_buttons', sharebar_buttons_def()));
  if (array_key_exists($name, $buttons)) {
    $button[] = $buttons[$name]->machine_name;
    return reset($button);
  }
}

/**
 * Form builder: Configure the sharebar system.
 */
function sharebar_settings() {
  $path = libraries_get_path('colorpicker');

  drupal_add_css($path . '/css/colorpicker.css');
  drupal_add_js($path . '/js/colorpicker.js');
  drupal_add_js(drupal_get_path('module', 'sharebar') . '/js/colorpicker.js');

  $form['buttonsset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Buttons'),
    '#description' => t('The following buttons are added by default in sharebar. You might wanna clear the cache after Add/edit/delete operation on buttons if changes not being reflected.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['buttonsset']['buttons'] = array(
    '#theme' => 'sharebar_buttons_table',
    '#weight' => 0,
  );

  // Display options.
  $form['displayoptions'] = array(
    '#type' => 'fieldset',
    '#weight' => 2,
    '#title' => t('Display options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['displayoptions']['sharebar_bar_horizontal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display horizontal Sharebar if the page is resized to less than 1000px?'),
    '#default_value' => variable_get('sharebar_bar_horizontal', TRUE),
  );

  $form['displayoptions']['sharebar_bar_onblock'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display sharebar as a block.'),
    '#default_value' => variable_get('sharebar_bar_onblock', TRUE),
  );

  $form['displayoptions']['sharebar_bar_credit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display credit link back to the Sharebar plugin? If disabled, please consider donating.'),
    '#default_value' => variable_get('sharebar_bar_credit', TRUE),
  );

  $form['displayoptions']['sharebar_bar_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom CSS Container when displayed in any region'),
    '#description' => t('Only id selector is supported.'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_id', 'sharebar'),
  );

  $form['displayoptions']['sharebar_bar_idhorizontal'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom CSS Container when displayed horizontally'),
    '#description' => t('Only id selector is supported.'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_idhorizontal', 'sharebarx'),
    '#states' => array(
      'visible' => array(
        ':input[name="sharebar_bar_horizontal"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['displayoptions']['sharebar_bar_toptoffset'] = array(
    '#type' => 'textfield',
    '#title' => t('Top Offset'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_toptoffset', 0),
  );

  $form['displayoptions']['sharebar_bar_position'] = array(
    '#type' => 'select',
    '#title' => t('Sharebar Position'),
    '#description' => t('Respective to the region, sharebar is being displayed in.'),
    '#default_value' => variable_get('sharebar_bar_position', 'none'),
    '#options' => array('none' => 'None', 'left' => 'Left', 'right' => 'Right'),
  );

  $form['displayoptions']['sharebar_bar_leftoffset'] = array(
    '#type' => 'textfield',
    '#title' => t('Left Offset'),
    '#description' => t('Used when positioned to left.'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_leftoffset', 10),
  );

  $form['displayoptions']['sharebar_bar_rightoffset'] = array(
    '#type' => 'textfield',
    '#title' => t('Right Offset'),
    '#description' => t('Used when positioned to right.'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_rightoffset', 10),
  );

  $form['displayoptions']['sharebar_bar_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum width in pixels required to show vertical Sharebar to the left of post'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_width', 1000),
    '#required' => TRUE,
  );

  $form['displayoptions']['sharebar_info'] = array(
    '#markup' => t('<b>Note:</b> "Display sharebar as a block" option must always be checked/enabled.'),
  );

  // Customize.
  $sitename = variable_get('site_name', '');

  $form['customize'] = array(
    '#type' => 'fieldset',
    '#weight' => 3,
    '#title' => t('Customize'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['customize']['sharebar_bar_swidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Sharebar Width'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_swidth', 75),
  );

  $form['customize']['sharebar_bar_twitter_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Username'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_twitter_username', $sitename),
  );

  $form['customize']['sharebar_bar_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Sharebar Background Color'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_background', 'FFFFFF'),
  );

  $form['customize']['sharebar_bar_border_style'] = array(
    '#type' => 'select',
    '#title' => t('Sharebar Border Style'),
    '#default_value' => variable_get('sharebar_bar_border_style', 'solid'),
    '#options' => array(
      'none' => 'none',
      'dotted' => 'dotted',
      'dashed' => 'dashed',
      'solid' => 'solid',
      'double' => 'double',
      'groove' => 'groove',
      'ridge' => 'ridge',
      'inset' => 'inset',
      'outset' => 'outset'),
  );
  $form['customize']['sharebar_bar_border_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Sharebar Border Width'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_border_width', '1px'),
  );
  $form['customize']['sharebar_bar_border'] = array(
    '#type' => 'textfield',
    '#title' => t('Sharebar Border Color'),
    '#size' => 10,
    '#default_value' => variable_get('sharebar_bar_border', 'CCCCCC'),
  );

  return system_settings_form($form);
}

/**
 * Function to get settings.
 */
function sharebar_get_setting_str($str, $tag) {
  $n1 = strpos($str, $tag) + drupal_strlen($tag) + 1;
  $n2 = strpos($str, $tag, $n1) - 2;
  return drupal_substr($str, $n1, $n2 - $n1);
}

/**
 * Provide a single block from the administration menu as a page.
 */
function sharebar_admin_menu_block_page() {
  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }
  return $output;
}
