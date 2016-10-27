<?php

/**
 * @file
 */
function diversity_preprocess_islandora_solr(&$variables) {
  $test_html = "drupalsolr search results";
  $results = $variables['results'];
  foreach ($results as $key => $result) {
    $drupal_result = $result['solr_doc']; //a Drupal search result
    if (isset($drupal_result['bundle_name'])) //only Drupal results have the 'bundle_name' element
    {
      /* Set Drupal search result thumbnails based on content type */
      $bundle = $drupal_result['bundle_name'];
      $content_type = $bundle['value']; //Drupal content type
      if ($content_type == 'Blog entry') { //content type: blog entry
        $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/blog.png';
      }
      else if ($content_type == 'Presentation') {//content type: presentation
        $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/presentation.png';
      }
      else if ($content_type == 'Spreadsheet') {//content type: spreadsheet
        $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/spreadsheet.png';
      }
      else if ($content_type == 'Word/Text Document') {//content type: word/text document
        $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/document_text.png';
      }
      else if ($content_type == 'Notebook') {//content type: book page
	     $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/book.png';
      }
      else if ($content_type == 'Calendar Event') {//content type: calendar event
	     $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/calendar.png';
      }
      else { //content type not defined above (default image)
        $result['thumbnail_url'] = 'sites/diversity.new.cairnrepo.org/files/search_thumbnails/default.png';
      }
      /* Set Drupal search result links */
      $node_url_array = explode("node/", $result['object_url']); //get node ID
      $node_id = $node_url_array[1]; //Drupal node ID
      $result['object_url'] = $drupal_result['url']['value'];//"node/" . $node_id; //Drupal node URL
    
    // Thumbnail.
      $path = url($result['thumbnail_url'], array('query' => $result['thumbnail_url_params']));
      $image = theme('image', array('path' => $path));

      $options = array('html' => TRUE);
      if (isset($result['object_label'])) {
       $options['attributes']['title'] = $result['object_label'];
      }
      if (isset($result['object_url_params'])) {
        $options['query'] = $result['object_url_params'];
      }
      if (isset($result['object_url_fragment'])) {
        $options['fragment'] = $result['object_url_fragment'];
      }
    
    // Thumbnail link.
      $variables['results'][$key]['thumbnail'] = l($image, $result['object_url'], $options);
      // make the label a link
      if(!empty($result['solr_doc']['label']['value'])){
        $variables['results'][$key]['solr_doc']['label']['value'] = l($result['solr_doc']['label']['value'], $result['object_url']);
      }
      // make the url a link
      if(!empty($result['solr_doc']['url']['value'])){
        $variables['results'][$key]['solr_doc']['url']['value'] = l($result['solr_doc']['url']['value'], $result['object_url']);
      }
    }
  }
}
