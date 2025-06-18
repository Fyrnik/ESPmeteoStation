#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>


const char* ssid = "WIFI_SSID";  // Название Вашей WiFi сети
const char* password = "WIFI_PASSWORD";  // Пароль Вашей WiFi сети
const String city = "CITY";  // Город, например - Moscow, Rybinsk, Yaroslavl
const String apiKey = "API_KEY";  // API ключ с сайта openweather.org
const int DisplayTime = 10;  // Время на одну страницу экрана в секундах
#define SCREEN_ADDRESS 0x3C  // Адрес экрана, может быть 0x3C либо 0x3D, поменяйте если экран не работает


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const char* host = "api.openweathermap.org";
float currentTemp = 0.0;
float feelsLike = 0.0;
int humidity = 0;
float pressure = 0.0;
float windSpeed = 0.0;
String windDirection = "";
String currentWeather = "";
unsigned long lastApiUpdate = 0;
unsigned long lastScreenSwitch = 0;
int currentScreen = 0;
const int numScreens = 6;
#define SDA_PIN 0
#define SCL_PIN 2

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED not found!");
    while (1)
      ;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected!");
  display.display();
  delay(1000);

  updateWeatherData();
}

void loop() {
  unsigned long currentMillis = millis() / 1000;

  // обновление данных каждые 60сек
  if (currentMillis - lastApiUpdate >= 60) {
    updateWeatherData();
    lastApiUpdate = currentMillis;
  }

  // переключение экранов
  if (currentMillis - lastScreenSwitch >= DisplayTime) {
    currentScreen = (currentScreen + 1) % numScreens;
    updateDisplay();
    lastScreenSwitch = currentMillis;
  }
}

void updateWeatherData() {
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";
  client.print(String("GET ") + url + " HTTP/1.1\r\n"
               + "Host: " + host + "\r\n"
               + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (!client.available() && millis() - timeout < 5000) {
    delay(10);
  }

  if (!client.available()) {
    Serial.println("No response");
    return;
  }

  // пропуск заголовков HTTP
  String line;
  do {
    line = client.readStringUntil('\r');
  } while (line != "\n");

  // парсинг JSON
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.println("JSON parse error");
    return;
  }

  // обновление данных
  currentTemp = doc["main"]["temp"];
  feelsLike = doc["main"]["feels_like"];
  humidity = doc["main"]["humidity"];
  pressure = doc["main"]["pressure"];
  windSpeed = doc["wind"]["speed"];
  windDirection = getWindDirection(doc["wind"]["deg"].as<int>());
  currentWeather = doc["weather"][0]["description"].as<String>();

  currentWeather = shortenWeatherDescription(currentWeather);  // сокращение

  updateDisplay();
}

// направление ветра
String getWindDirection(int deg) {
  if (deg >= 337.5 || deg < 22.5) return "N";
  if (deg >= 22.5 && deg < 67.5) return "NE";
  if (deg >= 67.5 && deg < 112.5) return "E";
  if (deg >= 112.5 && deg < 157.5) return "SE";
  if (deg >= 157.5 && deg < 202.5) return "S";
  if (deg >= 202.5 && deg < 247.5) return "SW";
  if (deg >= 247.5 && deg < 292.5) return "W";
  if (deg >= 292.5 && deg < 337.5) return "NW";
  return "?";
}

// сокращение
String shortenWeatherDescription(String description) {
  description.toLowerCase();
  if (description == "heavy intensity rain") return "Heavy rain";
  return description;
}

void updateDisplay() {
  display.clearDisplay();

  switch (currentScreen) {
    case 0:  // температура
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("TEMP");
      display.setTextSize(4);
      display.setCursor(0, 25);
      display.print(currentTemp, 1);
      display.setTextSize(1);
      display.print("o");
      display.setTextSize(2);
      display.print("C");
      break;

    case 1:  // ощущаемая температура
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("FEELS LIKE");
      display.setTextSize(4);
      display.setCursor(0, 25);
      display.print(feelsLike, 1);
      display.setTextSize(1);
      display.print("o");
      display.setTextSize(2);
      display.print("C");
      break;

    case 2:  // погода
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("WEATHER");
      display.setTextSize(2);
      display.setCursor(0, 20);
      display.println(currentWeather);
      break;

    case 3:  // влажность
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("HUMIDITY");
      display.setTextSize(4);
      display.setCursor(0, 25);
      display.print(humidity);
      display.setTextSize(2);
      display.print(" %");
      break;

    case 4:  // давление
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.println("PRESSURE");
      display.setTextSize(3);
      display.setCursor(0, 20);
      display.print(pressure);
      display.setCursor(0, 45);
      display.setTextSize(2);
      display.println("       hPa");
      break;

    case 5:  // ветер
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("WIND    ");
      display.println(windDirection);
      display.setTextSize(4);
      display.setCursor(0, 20);
      display.print(windSpeed, 1);
      display.setTextSize(1);
      display.print(" m/s");
      break;
  }

  display.display();
}