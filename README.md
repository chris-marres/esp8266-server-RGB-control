## esp8266-server-RGB-control

This project was developed using the platfromIO extension of Visual Studio Code. The [code](source/main.cpp) creates a web server hosted on an ESP8266 NodeMCU board and controls a WS2812B individually addressable RGB Led strip.

### HTTP Requests
The server listens and replies to the following url formats.
* http://[address]/ -> (200, "text/plain", "Someone Connected!!")

* http://[address]/RGB?Red=[RedValue]&Green=[GreenValue]&Blue=[BlueValue]&Group=[GroupIndex] -> Turns all the led's in group "GroupIndex" to the color (RedValue, GreenValue, BlueValue).

### Notes
In order for the code to actually work, you need to do a few adjustments.
* Change the ssid and password variables in order for the server to connect to the local wifi network.

* Change the PIN variable to the pin number the data line is connected to.

* Change the TOTAL_LEDS variable to the total amount of leds in the led strip.

In the main [program](source/main.cpp) the "Groups" array specifies the groups, in which the led strip will be divided, that can individually be controlled.
