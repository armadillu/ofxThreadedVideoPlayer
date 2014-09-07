OSX-only video playback addon based on ofxAVFVideoPlayer. Allows to load movies on the fly in a background thread without hiccups.

The main goal while creating this was to minimize the stuttering that happens when loading / unloading ofxAVFVideoPlayer videos on the fly as the app runs. 

it requires OSX, libc++.dylib, AVFoundation.framework, QuartzCore.framework, and CoreMedia.framework.