#include <ESP8266WiFi.h>//библиотека для подключения WiFi модуля 
#include <ESP8266WebServer.h>//библиотека для создания сервера
#include <ArduinoOTA.h>//библиотека для обновления по WiFi

#include "Adafruit_MQTT.h"//библиотека для подключения к MQTT серверу
#include "Adafruit_MQTT_Client.h"//библиотека для подключения к MQTT серверу
#define MQTT_SERV "io.adafruit.com"//арес сервера
#define MQTT_PORT 1883//порт для подключения
#define MQTT_NAME "KIRILLL"// Имя учетной записи
#define MQTT_PASS "c19cade9b7874c0cb46643269d1351fa"// пароль учетной записи

WiFiClient client; //инициализация WiFi клиента
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);//запуск WiFi клиента

//подписка на обновление данных сервера
Adafruit_MQTT_Subscribe room1 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smarthome.room1"); //подписка на обновление данных сервера
Adafruit_MQTT_Subscribe room2 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smarthome.room2");//подписка на обновление данных сервера
Adafruit_MQTT_Subscribe room3 = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smarthome.room3");//подписка на обновление данных сервера
Adafruit_MQTT_Subscribe lamp = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smarthome.lamp-out");//подписка на обновление данных сервера

Adafruit_MQTT_Publish tempinprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.temp-in");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish tempoutprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.temp-out");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish huminprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.hum-in");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish humoutprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.hum-out");//отправка обновленных данных на сервер

Adafruit_MQTT_Publish room1print = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.room1");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish room2print = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.room2");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish room3print = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.room3");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish lampprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.lamp-out");//отправка обновленных данных на сервер

Adafruit_MQTT_Publish doorprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.door");//отправка обновленных данных на сервер
Adafruit_MQTT_Publish garageprint = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smarthome.garage");//отправка обновленных данных на сервер

int8_t ret;//проверка подключения к серверу
uint8_t retries = 3;//проверка подключения к серверу


//const char* ssid = "Keenetic-6459";   const char* password = "qAuDsTuSGH";//логин и пароль роутера
const char* ssid = "Smarthome3";   const char* password = "12345679";//логин и пароль роутера
IPAddress ip;
//IPAddress ip (192, 168, 43, 94);//локальный ip //не забывай про обновление 94 -я 209- влад
IPAddress gateway (192, 168, 43, 1);//адрес роутера в сети
IPAddress subnet (255, 255, 255, 0);//макска подсети

String msg = " ";//переменная для хранения входящих сообщений
String chek_msg = " ";//переменная для хранения исходящих сообщений
int Nano_Errors = 0;// количество неудачных попыток соедениться с ардуино нано

#include "DHT.h"// Библиотека датчика температуры и влажности
#define DHTPIN D2 // вывод к датчику температуры и влажности
#define DHTTYPE DHT11//тип датчика температуры и влажности
DHT dht(DHTPIN, DHTTYPE);//инициализация датчика температуры и влажности

float h , temp_C, f , h_o, t_o;//переменные для хранения показаний температуры и влажности
String mmm;

int Lamp_mode = 2;//режим фонаря

const char* host_p = "192.168.43.113";//подвал
const char* host_p_sv = "192.168.43.114";//подвал свет
const char* host_p_v = "192.168.43.115";//подвал выключатель
const uint16_t port = 80;//порт сервера esp8266

ESP8266WebServer server(port);//инициализация сервера esp8266

int pub = 1;//переменная для очередной отправки данных на сервер adafruit
int led = D0;// вывод к светодиоду на первом этаже
int led2 = D1;// вывод к светодиоду на втором этаже
int led3 = D3;// вывод к светодиоду на третьем этаже
int led_sost = 0;// состояние светодиода на первом этаже
int led2_sost = 0;// состояние светодиода на втором этаже
int led3_sost = 0;// состояние светодиода на третьем этаже

String webPage = "";//переменная для хранения html страницы
String SVET = "";//переменная для интерфейса html страницы
String SVET_AUTO = "background: #FFD700;";//переменная для интерфейса html страницы
String DOOR = "";//переменная для интерфейса html страницы
String GARAGE = "";//переменная для интерфейса html страницы
String DOOR_AUTO = "background: #FFD700;";//переменная для интерфейса html страницы
String GARAGE_AUTO = "background: #FFD700;";//переменная для интерфейса html страницы
String ROOM1 = "";//переменная для интерфейса html страницы
String ROOM2 = "";//переменная для интерфейса html страницы
String ROOM3 = "";//переменная для интерфейса html страницы


unsigned long current_time, start_time,  error_time, last_time, last_time_publish, t, Timer = 1;//временные переменные



void setup(void) {//цикл инициализации
  pinMode(led, OUTPUT);// инициализация вывода как выход
  digitalWrite(led, led_sost);//присвоение логического состояния выводу
  pinMode(led2, OUTPUT);// инициализация вывода как выход
  digitalWrite(led2, led2_sost);//присвоение логического состояния выводу
  pinMode(led3, OUTPUT);// инициализация вывода как выход
  digitalWrite(led3, led3_sost);//присвоение логического состояния выводу

  Serial.begin(115200);//старт сериал порта
  WiFi.mode(WIFI_STA);//режим станции(подключение к действующей точке доступа)
  //WiFi.config(ip, gateway, subnet);//конфигурация WIFI соединения
  WiFi.begin(ssid, password); //старт WIFI соединения

  Serial.println("");
  Serial.println("RESET");//перезагрузка ардуино нано

  while (WiFi.status() != WL_CONNECTED) { // ждем соединения
    delay(50);
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());//вывод локального IP устройства
 ip =WiFi.localIP();
  dht.begin();//старт датчика влажности

  getTemperature();// функция получения температуры с датчика
  web();//функция формирования html страницы с обновленными переменными
  command();//инициализация возможных запросов и назначение ответных действий
  ArduinoOTA.setPort(8266);// порт для обновления по WiFi
  ArduinoOTA.setHostname("Smart");// имя устройства для обновления по WiFi

  ArduinoOTA.begin();//старт возможности беспроводного обновления

  mqtt.subscribe(&room1);//проверка состояний выключателя на сервере
  mqtt.subscribe(&room2);//проверка состояний выключателя на сервере
  mqtt.subscribe(&room3);//проверка состояний выключателя на сервере
  mqtt.subscribe(&lamp);//проверка состояний выключателя на сервере
  MQTT_connect();//функция обмена данными с удаленным сервером
  room1print.publish("OFF");// выключение выключателя на сервере
  room2print.publish("OFF");// выключение выключателя на сервере
  room3print.publish("OFF");// выключение выключателя на сервере
  lampprint.publish("OFF");// выключение выключателя на сервере
  doorprint.publish("закрыта");// выключение выключателя на сервере
  garageprint.publish("закрыт");// выключение выключателя на сервере
}

void loop(void) {//бесконечный цикл
  current_time = millis();//присваем переменной время работы мк со старта
  if (current_time - last_time >= 1000 ) {
    //если время сейчас больше чем в прошлый раз больше чем на секунду
    MQTT_main();//отправляем данные на сервер
    getTemperature();//проверяем температуру и влажность
    last_time = millis();//сбрасываем счетчик
  }

  uart();//проверяем не пришло ли сообщение от ардуино нано
  server.handleClient();//обрабатываем клиента при наличии
  ArduinoOTA.handle();//при наличии обновления- устанавливаем
}
