# yakt122
Yet another Model M Terminal 122 PS/2 to USB adapter

Inspired by Terminal-J project (https://github.com/jpagliaccio/Terminal-J) check that one out for hardware references.

This framwork lends itselve to more arbitrary code execution with key events in either downstroke or in some cases 
upstroke combinations.  With a PS2 key event, there is a first pass looking for a call back function to execute.  Most currently
go to a mapping of mode by key mapping where the default behaviour is to pass through the mode value.  The key-down+key-up keys 
(CTRL, ALT, SHIFT, CAPS-LOCK ** NOTE GUI key missing on Terminal 122 **) have up key events and these key events have different 
function calls in order to capture state.

You'll note that I also borrow the Arduino Keyboard class by copying here and altering one of the methods to make it public.

Enjoy!
