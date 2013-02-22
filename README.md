Migrate World Database
======================

This repository is used to store an implementation of the [Migrate API](http://drupal.org/project/migrate) in [Drupal](http://drupal.org/download) by using the data provided by the [MySQL world example database](http://dev.mysql.com/doc/index-other.html)

Installation
============

To properly use the example, please import the given database file `data/world_innodb.sql.gz` into a separate database on your system.


Please check that you add this new database to your Drupal configuration in `sites/default/settings.php` using an `example` key in the PHP array.

Here follows an example of database configuration settings. Please replace the information with your current MySQL configuration.

```php
$databases = array (
  'default' => array (
    'default' => array (
      'database' => 'drupal',
      'username' => 'root',
      'password' => 'root',
      'host' => 'localhost',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),
  'example' => array (
      'database' => 'world_innodb',
      'username' => 'root',
      'password' => 'root',
      'host' => 'localhost',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),
  ),
);
```

Finish the installation by adding the `migrate_world_database` folder to your `sites/all/modules/custom` directory and enabling it in Drupal.