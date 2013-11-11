Cadenza-Music-Notation-Software
===============================

An early version of stylus-controlled music notation.

by Gabe Montague

RUNNING
=======
Prebuilt for Mac OSX 10.8 and later.

To build on a mac, install XCode 4.6.3 and open Cadenza.xcodeproj in source/build1. This application uses the AGK/GLFW framework (not completely included), so it will ultimately be buildable for Windows, iOS, and Android as well as OS X.

Note: to best fit the dimension of your display, open source/build1/CoreForApp.h and change the WIDTH/HEIGHT options to a comfortable resoltion.

INTERACTION
===========
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
- Home moves the playhead back to the beginning.

HOW IT WORKS
============

At the core of Cadenza is a custom set of music-rendering functions I built.

To create a simple chord progression split between two staves, the following code would be used: (in MainCreateNew)
```c
// Add a new music score to the project. Pages of staff-systems with single staves are automatically generated.
NewTab( MUSIC_FULL );

// Add a new stave to the first staff system on the page. In the future we would specify the instrument too.
// Format: NewStave(int pageNum, int staffSystemNum)
NewStave(ac, 0);
                    // Passing the constant 'ac' tells Cadenza to find the first staff system in
                    // the entire score, whereas calling NewStave(0, 0) would act upon the first
                    // system of the first page. 'ac' (Auto-calculate) can be used for any 
                    // rendering function.


// Auto-arrange our staff-systems to look nice, starting on the first staff system (0)  of the first page (0)
ArrangeStaffSystems(0, 0);

// Split our staff system up into 4 measures by placing 3 barlines.
// Format: NewBarLineSplitStaffSystemPercent(int pageNum, int staffSystemNum, float percentOfWidth)
NewBarLineSplitStaffSystemPercent(ac, 0, 25.0f);
NewBarLineSplitStaffSystemPercent(ac, 0, 50.0f);
NewBarLineSplitStaffSystemPercent(ac, 0, 75.0f);

// Subbarlines break up measures into segments of time. Add 4 subbarlines (4 beats) to measure 1.
// Format: NewBarLineSplitMeasurePercent(int pageNum, int staffSystemNum, int measureNum,
//  float percentOfWidth, double timeInterval)
NewBarLineSplitMeasurePercent(ac, ac, 0, 20.0f, 0); // At the first beat no time has passed
NewBarLineSplitMeasurePercent(ac, ac, 0, 40.0f, 0.25); // 0.25 is a 1/4 note
NewBarLineSplitMeasurePercent(ac, ac, 0, 60.0f, 0.25);
NewBarLineSplitMeasurePercent(ac, ac, 0, 80.0f, 0.25);

// Finally, add some notes to our four beats
// Format: NewNote( int pageNum, int staffSystemNum, int subbarLineNum, int staveNum,
//  noteLetterEnum letter, char octaveNum, noteAccidentalEnum accidentalName )

NewNote(ac, ac, 0, 0, nC, 4, naNone); // Adds the note C4 to the first barline of the upper stave
NewNote(ac, ac, 0, 0, nE, 3, naNone);
NewNote(ac, ac, 0, 0, nG, 3, naNone); // We have a 1st-inversion C-chord in our right hand!

NewNote(ac, ac, 0, 1, nC, 3, naNone); // Adds the bass note C3 to the the lower stave

// Now let's do the three other beats...
NewNote(ac, ac, 1, 0, nC, 4, naNone);
NewNote(ac, ac, 1, 0, nA, 3, naNone);
NewNote(ac, ac, 1, 0, nF, 3, naNone);
NewNote(ac, ac, 1, 1, nC, 3, naNone); // An F chord

NewNote(ac, ac, 2, 0, nB, 3, naNone);
NewNote(ac, ac, 2, 0, nG, 3, naNone);
NewNote(ac, ac, 2, 0, nF, 3, naNone);
NewNote(ac, ac, 2, 1, nD, 3, naNone); // A G7 chord

NewNote(ac, ac, 3, 0, nC, 4, naNone);
NewNote(ac, ac, 3, 0, nG, 3, naNone);
NewNote(ac, ac, 3, 0, nE, 3, naNone);
NewNote(ac, ac, 3, 1, nC, 3, naNone); // Another C chord
```
