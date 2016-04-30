<?php

/**
 * @file
 * Contains touch-site drush command.
 */

use Drupal\Core\Url;
use Drupal\Component\Utility\Timer;
use GuzzleHttp\Exception\RequestException;

/**
 * Implements hook_drush_command().
 */
function touch_site_drush_command() {
  $items['touch-site'] = array(
    'description' => 'Makes an http request to the front page.',
    'aliases' => array('ts'),
  );
  return $items;
}

/**
 * Callback function for touch-site command.
 */
function drush_touch_site() {

  $drupal_major_version = drush_drupal_major_version();

  if ($drupal_major_version == 7) {
    $url = url(NULL, array('absolute' => TRUE));
    timer_start('ts');
    $result = drupal_http_request($url);
    $time = timer_read('ts');
    if (isset($result->error)) {
      $error = $result->code ? "$url => {$result->code} [{$result->error}]" : "$url => {$result->error}";
      return drush_set_error($error);
    }

    drush_print("$url => {$result->code} [{$result->status_message}] - $time ms");
  }
  elseif ($drupal_major_version == 8) {
    $url = Url::fromUri('internal:/', array('absolute' => TRUE))->toString();
    $client = \Drupal::httpClient();
    try {
      Timer::start('ts');
      $response = $client->get($url);
      $time = Timer::read('ts');
    }
    catch (RequestException $e) {
      return drush_set_error("$url => {$e->getMessage()}");
    }

    drush_print("$url => {$response->getStatusCode()} [{$response->getReasonPhrase()}] - $time ms");
  }
  else {
    return drush_set_error('This Drupal version is not supported.');
  }

}
