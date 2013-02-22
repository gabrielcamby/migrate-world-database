<?php
/**
 * @file
 * migrate_world_database.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function migrate_world_database_taxonomy_default_vocabularies() {
  return array(
    'countries' => array(
      'name' => 'Countries',
      'machine_name' => 'countries',
      'description' => 'Represents a list of countries for the Migrate World Database example',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'languages' => array(
      'name' => 'Languages',
      'machine_name' => 'languages',
      'description' => 'Represents a list of languages for the Migrate World Database example',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
