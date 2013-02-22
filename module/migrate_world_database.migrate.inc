<?php

class CityMigration extends Migration {

	public function __construct() {
		parent::__construct();

		$this->dependencies = array('Country');

		$this->description = t('Import world city data from example database.');

		$this->map = new MigrateSQLMap($this->machineName,
						array(
							'ID' => array(
								'type' => 'int',
								'length' => 11,
								'not null' => TRUE,
							)
						),
						MigrateDestinationNode::getKeySchema()
		);

		$query = Database::getConnection('example')->select('City', 'c')
				->fields('c', array('ID', 'Name', 'CountryCode', 'District', 'Population'))
				->orderBy('ID', 'ASC');
		$this->source = new MigrateSourceSQL($query);

		$this->destination = new MigrateDestinationNode('city');

		// Adds all mappings used by migration fields
		$this->addFieldMapping('title', 'Name');
		$this->addFieldMapping('field_city_population', 'Population')
				->defaultValue(0);
		$this->addFieldMapping('field_city_country', 'CountryCode')
				->sourceMigration('Country')
				->arguments(array('source_type' => 'tid'));

		// Maps all source unused fields to NULL key
		$this->addFieldMapping(NULL, 'ID');
		$this->addFieldMapping(NULL, 'District')
				->description('District not needed');

		// Maps all destination unused fields
		$this->addUnmigratedDestinations(array('is_new', 'created', 'changed',
			'status', 'promote', 'revision', 'language', 'revision_uid', 'log', 'tnid',
			'body:format', 'comment'));
	}

}

class CountryMigration extends Migration {

	public function __construct() {
		parent::__construct();

		$this->dependencies = array('Language');

		$this->description = t('Import country city data from example database.');

		$this->map = new MigrateSQLMap($this->machineName,
						array(
							'Code' => array(
								'type' => 'varchar',
								'length' => 3,
								'not null' => TRUE,
							)
						),
						MigrateDestinationTerm::getKeySchema()
		);

		$query = Database::getConnection('example')->select('Country', 'c');
		$query->leftJoin('CountryLanguage', 'l', 'c.Code = l.CountryCode');
		$query->addExpression('GROUP_CONCAT(l.Language)', 'Languages');
		$query->fields('c', array('Code', 'Name'))
				->orderBy('Code', 'ASC');
		$query->where('l.IsOfficial = :official', array(':official' => 'T'));
		$query->groupBy('c.Code');
		$this->source = new MigrateSourceSQL($query);

		$this->destination = new MigrateDestinationTerm('countries');

		// Adds all mappings used by migration fields
		$this->addFieldMapping('name', 'Name');
		$this->addFieldMapping('field_country_abbreviation', 'Code');

		$this->addFieldMapping('field_country_language', 'Languages')
				->separator(',')
				->sourceMigration('Language')
				->arguments(array('source_type' => 'tid'))
		;

		// Maps all destination unused fields
		$this->addUnmigratedDestinations(array('description', 'parent', 'parent_name',
			'format', 'weight', 'field_country_abbreviation:language'));
	}

}

class LanguageMigration extends Migration {

	public function __construct() {
		parent::__construct();

		$this->description = t('Import language data from example database.');

		$this->map = new MigrateSQLMap($this->machineName,
						array(
							'Language' => array(
								'type' => 'varchar',
								'length' => 30,
								'not null' => TRUE,
							)
						),
						MigrateDestinationTerm::getKeySchema()
		);

		$query = Database::getConnection('example')->select('CountryLanguage', 'c')
				->distinct()
				->fields('c', array('Language'))
				->orderBy('Language', 'ASC');
		$this->source = new MigrateSourceSQL($query);

		$this->destination = new MigrateDestinationTerm('languages');

		// Adds all mappings used by migration fields
		$this->addFieldMapping('name', 'Language');

		// Maps all destination unused fields
		$this->addUnmigratedDestinations(array('description', 'parent', 'parent_name',
			'format', 'weight', 'field_country_abbreviation:language'));
	}

}

?>