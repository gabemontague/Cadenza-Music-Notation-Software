Cadenza-Music-Notation-Software
===============================

An early version of stylus-controlled music notation.

by Gabe Montague

RUNNING:
Prebuilt for Mac OSX 10.8 and later.

To build on a mac, install XCode 4.6.3 and open Cadenza.xcodeproj in source/build1. This application uses the AGK/GLFW framework (not completely included), so it will ultimately be buildable for Windows, iOS, and Android as well as OS X.

Note: to best fit the dimension of your display, open source/build1/CoreForApp.h and change the WIDTH/HEIGHT options to a comfortable resoltion.

INTERACTION:
For best effect, use with tablet (such as intuos). Using the mouse will be more difficult, but it will work too.

- Left mouse button draws.
- Right mouse button scrolls.
- Drawing:
  The two currently recognized gestures are barlines and solid noteheads. Try drawing them in. Notice that the playback cursor will adjust to fit your divisions in time accordingly. Solid noteheads are by default treated as quarter notes during playback.
- Spacebar plays/pauses.
- Use the up and down arrow keys to control the playhead position.
- Control-up/down toggles the view between spread, column, and double-column views.

Less important shortcuts:
- Control-` (tilda key) switches the current tab.
- Control-w closes the current tab
- Use the -/= keys to zoom in and out (feature still in development)
  
