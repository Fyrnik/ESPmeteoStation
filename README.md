Small weather station on ESP-01 and SSD1306

![scheme](https://github.com/user-attachments/assets/1112834c-2890-4bea-8467-d9f5f66d23fd)

ENG:
To download the firmware you will need a computer, Arduino IDE program, programmer for ESP-01, connection to WiFi network

Before uploading the firmware replace the parameters:
1. "WIFI_SSID" for the name of your WiFi network
2. "WIFI_PASSWORD" for the password of your WiFi network
3. "CITY" for your city
4. "API_KEY" for your API key from the website https://openweathermap.org

If the display doesn't work, change the SCREEN_ADDRESS parameter from 0x3C to 0x3D


OBTAINING AN API KEY
1. Go to https://openweathermap.org and register
2. After registering click on your profile, then click on "My API keys"
3. Copy the API key, or create a new one by entering the key name and clicking Generate
4. Insert the key into the firmware


To upload the firmware:
1. Connect the programmer with ESP-01 to the computer via USB
2. Move the file "meteo.ino" to the desktop and open it with the Arduino IDE software, the program will place it into the folder with the file name
3. Click File > Preferences and in the bottom field paste the link:   http://arduino.esp8266.com/stable/package_esp8266com_index.json.
4. Click Tools > Board > Boards Manager and then type esp8266 in the search field and click on the INSTALL button that appears.
5. After installation, select Tools > Board > esp8266 > Generic ESP8266 Module
6. Click Sketch > Include library > Manage libraries and then in the search bar write the names of the following libraries and click INSTALL: Adafruit SSD1306, ArduinoJson.
7. Click Tools > Port and select a port on your board other than COM1 and COM3
8. On the top left of the screen, click the blue arrow button and upload the firmware! You can also do this by pressing Ctrl + U
![photo_2025-06-18_14-32-18](https://github.com/user-attachments/assets/a5740fbc-988e-4446-907b-8d10482acd5e)
![photo_2025-06-18_14-32-21](https://github.com/user-attachments/assets/d2beef02-ab7e-415f-9870-a68c32cc7982)


