# Touch site Drush command

A simple [Drush](https://github.com/drush-ops/drush) command that sends an http request to the front page of the Drupal site.

## Problem / Motivation
The first time you open your Drupal site after clearing cache using CLI tools (like Drush or Drupal Console) the access may be very slow. This command warms the cache by loading front page of the site.

## Usage
Run `drush touch-site` or `drush ts` in the site directory. You can "touch" your site immediatly after cache clearing as follows: `drush cc all && drush ts`. Notice that some Drush commads (like `drush en`) may clear Drupal cache implicitly.

## Requirements
You should specify url of the site by providing URI option. This can be done through command line as follows `drush ts --uri=http://localhost/path/to/drupal` or by using [drushrc.php](http://api.drush.org/api/drush/examples!example.drushrc.php/master) file (recommended way).
```php
<?php

// URI of the Drupal site to use.
$options['uri'] = 'http://localhost/path/to/drupal';
```
##  License
GNU General Public License, version 2



