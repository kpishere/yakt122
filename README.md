# yakt122
Yet another Model M Terminal 122 PS/2 to USB adapter

Inspired by Terminal-J project (https://github.com/jpagliaccio/Terminal-J) check that one out for hardware references.

This framework lends itself to more arbitrary code execution with key events in either downstroke or in some cases
upstroke combinations.  With a PS2 key events, there is a first pass looking for a call back function to execute.  Most currently
go to a mapping of mode by key mapping where the default behaviour is to pass through the mode value.  The key-down+key-up keys
(CTRL, ALT, SHIFT, CAPS-LOCK ** NOTE GUI key is left [Reset Quit] button and CTRL is [Enter] button on Terminal 122 **) have up key events and these key events have different function calls in order to capture state.

Notice that in this key mapping, the final symbols are getting split or joined between different key+mode combinations.

You'll also note that I borrow the Arduino Keyboard class by copying here and altering one of the methods to make it public so that we may send USB key events directly.  Basically, were just borrowing the USB HID keyboard definition.

Enjoy!

# For MacOS

For High Sierra and later, the keyboard drivers were updated.  Here is link of how to customize further. With it, you could probably activate F-keys F20 through F24.  As it is though, you can map upto F-19.  

[Remapping Keys in macOS 10.12 Sierra](https://developer.apple.com/library/archive/technotes/tn2450/_index.html)

[Apple Keyboard History](https://en.wikipedia.org/wiki/Apple_Keyboard)

# Example hardware implementation 

This Pro Micro device (Leanardo compatible) is a great one to use.  Further below is an image of a case (the case STL file is in the bom folder, found a use for those Mac Stickers!).

![Close up](https://user-images.githubusercontent.com/25204173/93367734-e7cc8580-f81a-11ea-8194-17ef17955601.JPG)

![With terminal 122](https://user-images.githubusercontent.com/25204173/93367741-ea2edf80-f81a-11ea-808e-f3e9ffaaed09.JPG)

![With Case](https://github.com/kpishere/yakt122/blob/master/bom/case_assembly.jpg?raw=true)
