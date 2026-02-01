# Rory's ESP32 LED Media Player
Simple WIFI media player on ESP32 for playing .RORY files.</br>
Media is played on 3 LEDs. </br>
<img width="400" height="840" alt="image" src="https://github.com/user-attachments/assets/ff284c91-83f8-490f-881a-fd861e571e8b" />


## How to get it up and running yourself:
### Requirements:
* ESP32
* 3 different colour LEDs
* a breadboard
* a USB A to USB C data cable
### Setup:
* Download and open the newest version of the Arduino IDE exe (or at least version 1.8), follow all instructions till it is installed and it should open on an unsaved file.
* In the top right, click on File > Preferences then under “Additional Boards Manager URLs”  paste the following link:
> https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
* Click the OK button to save the setting.
* Click on the Tools menu on the top menu bar.
* Then press Board > Boards Manager.
* Search and install esp32 by Expressive Systems and Arduino ESP32 Boards by Arduino.</br>
This should install everything you need.
* Go back to your unsaved file and paste in the code at the end of this document.
* Place your ESP32 in the breadboard so pins 17, 18, 19 and any GND pin are ready to use.
* Plug one LED into pin 18 and GND so it forms a circuit to turn on and off the left LED.
* Repeat with pins 19, the samee GND and your middle LED. Then again with 17, the same GND and your right LED.
* Plug the ESP32 into the computer using the data cable.
* Press the arrow in the top left corner of the IDE and let the code compile and upload to the micro controller.</br>
The media player should be ready!
### Use:
* From the screen you were at to upload the code, press CTR+SHIFT+M to open the Serial monitor and if you unplug and re-plugin your ESP32 it shoul come up with the line:
> Connected! IP address: 192.168.*.***
* Copy the IP address to the media player (ie. 192.168.0.89) and, in your browser search bar, go to http://<insert-IP-address> and it should bring up the media player's UI.
* Press the bottom button to play 'Mary Had a Little Lamb'
* or, press the top button to upload your own .RORY file
