# SpeedometerTester
Arduino project to test an electronic speedometer

A very simple project created to test an electronic speedometer. Specifically, I was testing a 16,000 pulse per mile gauge from Classic Instruments.

The project requires:
  - Arduino Uno
  - LCDKeypad Shield
  - Driver interface detailed in DriverCircuit.pdf
  
Additional libraries:
  - FlexiTimer2 (https://playground.arduino.cc/Main/FlexiTimer2)
  - LCDKeypad (https://github.com/dzindra/LCDKeypad)

You'll need to be able to attach the driver circuit to the Arduino. The version of the shield I used had thru-holes along the edge passing thru some of the unused connections. I was able to solder headers onto the shield and plug the dirver into those. Depending on the design of your shield you may need to find an alternative way to connect.

I also powered my Arduino thru the barrel connector using a 9V adapter plugged into the car's power outlet. This gave a common ground, so I only needed to ground the driver circuit to the Arduino. If you power your Arduino separatly, you'll need to run an additional ground from the Arduino to the car.

Connections:

Driver      Connect to
---------------------------
Ground      Arduino Gnd pin
Input       Arduino pin D2
+12         Car +12 (I used the power connection on the speedometer)
Output      Speedometer signal input

(Optional) Arduino ground to chassis ground if Arduino powered from a separate supply. I suggest the ground to the speedometer.

Usage:
After constructing tester and connecting to the speedometer, power things up. Most likely this means turning on your car. NOT starting the engine, just turn the switch to on! Especially important if you are in an enclosed garage, DO NOT run your car's engine!

Usage of the tester is pretty simple. The up and down buttons on the shield jog the MPH up or down in 5 MPH increments. The display shows the set speed and the output signal frequency sent to the speedometer. Ideally, your speedometer will show the same speed displayed on the tester!

If your speedometer is functioning but the speed is vastly wrong, you may have something other than a 16,000 PPM type. Best is to check the manufacturer data or search the web to figure out what you have, then try updating the PPM macro to match your speedometer. You may also need to experiment with tweaking the resolution. I HIGHLY recommend checking the output with a frequency counter to make sure you don't possibly damage your speedometer. These are VERY low frequencies - a few 100 Hz max.

You can find the expected frequency for a given MPH with:

f = (MPH x PPM) / 3600

Example:
At 45 MPH on a 16,000 PPM speedometer:

f = (45 x 16,000) / 3,600 = 200 Hz

DISCLAIMER:
This information is presented where-is, as-is, with no guarantees of any kind. The user (you) assumes all risks and is responsible for ensuring that any usage of any part of this project is done in a safe manner. Any damage or injury incurred as a result using any of this information is SOLELY the user's responsibility.
