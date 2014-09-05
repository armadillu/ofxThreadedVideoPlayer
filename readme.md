

OSX-only video playback addon based on ofxAVFVideoPlayer. Allows to load movies on the fly in a background thread without hicups, each movie instance is updates in its own thread. I get around 40 720p movie clips playing nicely, leaving room for the main thread to do other things.
_____

it requires a https://github.com/obviousjim/ofxAVFVideoPlayer fork on a very specific commit https://github.com/local-projects/ofxAVFVideoPlayer

This is actually not threaded anymore! only one of the branches is and it doesn't work well. What this adds is a threaded destructor which in my case seemed to be the slowest operation when handling many videos (unloading/deleting a video would take 40ms or so).

very messy!
