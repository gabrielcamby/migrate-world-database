<?php
/**
 * @file
 * migrate_world_database.features.inc
 */

/**
 * Implements hook_node_info().
 */
function migrate_world_database_node_info() {
  $items = array(
    'city' => array(
      'name' => t('City'),
      'base' => 'node_content',
      'description' => 'Represents a city for the Migrate World Database example',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
