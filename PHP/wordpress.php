// functions.php

function alx_embed_html( $html ) { return '<div class="video-container">' . $html . '</div>'; }
add_filter( 'embed_oembed_html', 'alx_embed_html', 10, 3 );
add_filter( 'video_embed_html', 'alx_embed_html' ); // Jetpack

// style.css

.video-container { position: relative; padding-bottom: 56.25%; height: 0; overflow: hidden; }
.video-container iframe, .video-container object, .video-container embed, .video-container video { position: absolute; top: 0; left: 0; width: 100%; height: 100%; }
