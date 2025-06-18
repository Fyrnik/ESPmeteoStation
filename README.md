Small weather station on ESP-01 and SSD1306

![scheme](https://github.com/user-attachments/assets/1112834c-2890-4bea-8467-d9f5f66d23fd)

ENG:
To download the firmware you will need a computer, Arduino IDE program, programmer for ESP-01, connection to WiFi network

Before uploading the firmware replace the parameters:
"WIFI_SSID" for the name of your WiFi network
"WIFI_PASSWORD" for the password of your WiFi network
"CITY" for your city
"API_KEY" for your API key from the website https://openweathermap.org

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

RU:
Для загрузки прошивки понадобится компьютер, программа Arduino IDE, программатор для ESP-01, подключение к WiFi сети

Перед загрузкой в файле прошивки "meteo.ino" замените параметры:
"WIFI_SSID" на имя Вашей WiFi сети
"WIFI_PASSWORD" на пароль Вашей WiFi сети
"CITY" на Ваш город
"API_KEY" на Ваш API ключ с сайта https://openweathermap.org

Если экран не работает, поменяйте параметр SCREEN_ADDRESS с 0x3C на 0x3D


ПОЛУЧЕНИЕ API КЛЮЧА
1. Зайдите на сайт https://openweathermap.org и зарегистрируйтесь
2. После регистрации справа сверху нажмите на Ваш профиль, затем нажмите на "My API keys"
3. Скопируйте API ключ из поля под надписью Key, либо создайте новый введя имя ключа и нажав кнопку Generate
4. Вставьте ключ в прошивку


Для загрузки прошивки:
1. Подключите программатор с ESP-01 к компьютеру по USB
2. Запустите файл "meteo.ino" в программе Arduino IDE, предварительно перенеся его на рабочий стол, программа поместит его в папку
3. Нажмите File > Preferences и в нижнее поле вствьте ссылку:  http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Нажмите Tools > Board > Boards Manager после чего в поле поиска напишите esp8266 и нажмите на появившуюся кнопку INSTALL
5. После установки нажмите Tools > Board > esp8266 > Generic ESP8266 Module
6. Нажмите Sketch > Include library > Manage libraries после чего в строке поиска поочередно пишите названия следующих библиотек и нажимайте INSTALL у библиотек с полностью совпадающим названием: Adafruit SSD1306, ArduinoJson
5. Нажмите Tools > Port и выберите порт вашей платы, отличный от COM1 и COM3
6. Слева сверху экрана нажмите голубую кнопку со стрелочкой и загрузите прошивку! Так же это можно сделать сочетанием Ctrl + U

![photo_2025-06-18_14-32-18](https://github.com/user-attachments/assets/a5740fbc-988e-4446-907b-8d10482acd5e)
![photo_2025-06-18_14-32-21](https://github.com/user-attachments/assets/d2beef02-ab7e-415f-9870-a68c32cc7982)


