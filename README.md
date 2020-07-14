# yakt122
Yet another Model M Terminal 122 PS/2 to USB adapter

Inspired by Terminal-J project (https://github.com/jpagliaccio/Terminal-J) check that one out for hardware references.

This framwork lends itself to more arbitrary code execution with key events in either downstroke or in some cases
upstroke combinations.  With a PS2 key events, there is a first pass looking for a call back function to execute.  Most currently
go to a mapping of mode by key mapping where the default behaviour is to pass through the mode value.  The key-down+key-up keys
(CTRL, ALT, SHIFT, CAPS-LOCK ** NOTE GUI key missing on Terminal 122 **) have up key events and these key events have different
function calls in order to capture state.

Notice that in this key mapping, the final symbols are getting split or joined between different key+mode combinations.

You'll also note that I also borrow the Arduino Keyboard class by copying here and altering one of the methods to make it public so that we may send USB key events directly.  Basically, were just borrowing the USB HID keybaord definition.

Enjoy!

# For MacOS

Sadly, the Apple driver AppleHIDKeyboard.kext only supports 10x type keyboards.  That means that all the other keys on the Terminal 122 keyboard can't be used with this driver on MacOS.

There are mapping tools like Ukelele, sure but they work after the keys presented from the driver so .. it does not help in this case.

Must hack/replace this driver to use the Terminal 122 keyboard and have it feel 'native'.
