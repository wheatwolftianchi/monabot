# monabot
control through signal_1.py through your serial ports available on your laptop/computer. 

input state that you want by using keyboard
 
 State Menu:
 - 0 - stop motors
 - 1 - forward
 - 2 - turning left
 - 3 - turning right
 - 4 - default on board route
 - 5 - start live program mode
 
 While in waiting for state layer, if you input a program, the monabot will immediatly start to perform the program you entre, the program syntax is the same as program mode syntax, this function can only be activated when the monabot is connected to the computer using cable, this function is mainly used for testing. In using, the usage of state 5 live program mode is highly recommanded. 
 
 # LED showing working condition
 There is a RGB LED on each side of the monabot. 
 When the monabot is waiting for command after you entre state 5, both LEDs will be light on with colour of light blue(0,255,255). The monabot will wait untill you entre a command no matter if it is correctly or not. 
 
 After a command is been received by the monabot, the robot will wait 15s before it activate the program, therefore you can use the time to remove the cable if you want. During this time, the LEDs will change time once every second, Blue(0,0,255) and Red(255,0,0). 
 
When the robot is running is actually moving along the programmed movements, the LEDs will both show a colour of Green(0,255,0). 

All LEDs will be off after a run is over and waiting for new state. 
 
 # Program mode sytax
 The command is a string that don't include any space, each command section is made up of one movement token and one length of movement token in second. e.g. f1 means f movement 1 second. 
 
 Movement token table
 - f - forward
 - b - backward
 - l - turning left
 - r - turning right
 
 The whole command can come up with multiple peices of command sections. 
 For example, f10l5r5b10 represents forward 10s -> turning left 5s -> turning right 5s -> backward 10s. 
 
