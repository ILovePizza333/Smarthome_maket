#include <Servo.h>//подключение библиотеки сервоприводов
#include <SPI.h>//Подключение библиотеки для работы шины SPI
#include <MFRC522.h>// подключение библиотеки для работы с RFID  
#define RST_PIN 9  //пин сброса для RFID считывателей
#define SS_PIN 8 //пин для выбора первого  RFID считывателя 
#define SS_PIN2 10  //пин для выбора второго  RFID считывателя
MFRC522 mfrc522(SS_PIN, RST_PIN);//   инициализация первого считывателя
MFRC522 garage_card(SS_PIN2, RST_PIN);//инициализация второго считывателя
MFRC522::MIFARE_Key key;//инициализация ключа
Servo home_servo;//инициализация первого серво
Servo garage_servo;//инициализация второго серво
Servo garage_servo2;//инициализация второго серво
String code_home = "201232218110";//переменная с записанным номером карты//201232218110
String code_garage = "8617249249";//переменная с записанным номером метки в машине//8617249249
String code_key="19215717639";//убрать
String u, u2;//переменные для хранения считываемых данных
int garage_auto = 1, home_auto = 1;//автоматический режим открытия дверей и ворот
unsigned long timeLast_garage, timeLast_home, curTime, last_av_time;//временные переменные
String DOOR_sost = "DOOR_CLOSE";//переменная состояния двери
String GARAGE_sost = "GARAGE_CLOSE";////переменная состояния ворот

char m;//переменная для входящих символов
String msg = " ";//переменная для входящего сообщения целиком
String klimat = "Ошибка";//хранение и отправка температуры и влажности на wemos

bool flag_garage;//состояние гаража
bool flag_home;//состояние двери дома

//подключение и инициализация датчика температуры и влажности
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
unsigned long  last_temp;
float h ;
float t;


//Подключение фонаря, датчика освещения, датчика движения
#define Lamp 5
#define Light_sensor A1
#define Motion_sensor A0
unsigned long last_motion, time_motion = 3000;
int Lamp_mode = 2, Light, Light_point = 300;



//настройки при включении
void setup() {
  pinMode(Lamp, OUTPUT);
  pinMode(Light_sensor, INPUT);
  pinMode(Motion_sensor, INPUT);
  digitalWrite(Lamp, LOW);

  Serial.begin(115200); // Обычная скорость передачи данных

  dht.begin();

  SPI.begin();        
  mfrc522.PCD_Init(); 
  garage_card.PCD_Init(); 
  garage_servo2.attach(3);
  garage_servo.attach(2);
  home_servo.attach(6);
  home_servo.write(90);
  garage_servo.write(110);  
  garage_servo2.write(0);

 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
  dump_byte_array2(key.keyByte, MFRC522::MF_KEY_SIZE);

}

void loop() {//бесконечный цикл
  uart();
  if (home_auto == 0) {
    timeLast_home = millis();
  }
  if (garage_auto == 0) {
    timeLast_garage = millis();
  }
  curTime = millis();
  if (curTime - last_temp  > 5000 ) {
    temp();
    last_temp = millis();
  }
  card_home();
  lamp();
  card_garage();
}
