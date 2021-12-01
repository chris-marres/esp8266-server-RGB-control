## esp8266-server-RGB-control

This project was developed using the platfromIO extension of Visual Studio Code. The code creates a web server hosted on an ESP8266 NodeMCU board and controls a WS2812B individually addressable RGB Led strip.

### Notes
In order for the code to actually work, you need to do a few adjustments.
* Change the ssid and password variables in order for the server to connect to the local wifi network.
* Change the PIN variable to the pin number the data line is connected to.
* Change the TOTAL_LEDS variable to the total amount of leds in the led strip.
