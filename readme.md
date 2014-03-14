OSX-only video playback addon based on ofxAVFVideoPlayer. Allows to load movies on the fly in a background thread without hicups, each movie instance is updates in its own thread. I get around 40 720p movie clips playing nicely, leaving room for the main thread to do other things.

it requires this:
https://github.com/obviousjim/ofxAVFVideoPlayer