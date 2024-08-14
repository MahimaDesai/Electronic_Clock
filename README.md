# Electronic_Clock
An electronic clock that displays time in hours and minutes.

# Requirements
The system will be developed based on Erika OS, using the RTE architecture and the Python Code Generator.

Button 1 and 2 will be used to control the clock. ev_KeyLeft will iterate through the various display and edit modes. ev_KeyRight will be used to increment the minute or hour widget.
Button 1 will create the event ev_KeyLeft.
Button 2 will fire the event ev_KeyRight.
If the Button 2 is pressed continuously for at least 1s, the event ev_RightLongPress will be fired.

In display mode, the clock numbers shall be shown as white letters on a black background. 
In Editing Mode, the letters (per widget, i.e. hours OR minutes) shall be shown as black letters on white background.

Active Object and Hierarchial state machine concepts can be preferred.
The state machine shall be implemented using a lookup table pattern. 
