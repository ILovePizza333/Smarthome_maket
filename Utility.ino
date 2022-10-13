
void MQTT_Publish() {
  switch (pub) {
    case 1:
      tempinprint.publish(temp_C);//публикуем значение температуры в доме
      break;
    case 2:
      huminprint.publish(h);//публикуем значение влажности в доме
      break;
    case 3:
      tempoutprint.publish(t_o);//публикуем значение температуры на улице
      break;
    case 4:
      humoutprint.publish(h_o);//публикуем значение влажности на улице
      break;
    case 5:
      if (led_sost == 0)      room1print.publish("OFF");
      if (led_sost == 1)      room1print.publish("ON");
      break;
    case 6:
      if (led2_sost == 0)      room2print.publish("OFF");
      if (led2_sost == 1)      room2print.publish("ON");
    case 7:
      if (led3_sost == 0)      room3print.publish("OFF");
      if (led3_sost == 1)      room3print.publish("ON");
      break;
    case 8:
      if (SVET == "background: #FFD700;")      lampprint.publish("ON");
      if (SVET == "")      lampprint.publish("OFF");

      break;
    case 9:
      if (DOOR == "")  doorprint.publish("закрыта");
      if (DOOR == "background: #FFD700;")  doorprint.publish("открыта");
      break;
    case 10:
      if (GARAGE == "background: #FFD700;")  garageprint.publish("закрыт");
      if (GARAGE == "")  garageprint.publish("открыт");
      break;

      break;
  }


}
void MQTT_main() {
  MQTT_connect();//подключение к MQTT серверу
  if (current_time - last_time_publish >= 3000 ) {
    MQTT_Publish();//публикуем одно из текущих значений переменных
    pub++;//прибавляем значение к переменной, чобы в следующий опубликовать другую
    if (pub >= 5) {//если зашли за границу
      pub = 1;//сбрасываем
    }

    last_time_publish = millis();//сбрасываем счетчик
  }

  //проверяем подписки, если есть изменения- обрабатываем
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(1000)))  {// стандарт 5000
    if (subscription == &room1)    {
      if (!strcmp((char*) room1.lastread, "ON"))      {
        led_sost = 1;
        digitalWrite(led, led_sost);
      } else {
        led_sost = 0;
        digitalWrite(led, led_sost);
      }
    }
    if (subscription == &room2)    {
      if (!strcmp((char*) room2.lastread, "ON"))      {
        led2_sost = 1;
        digitalWrite(led2, led2_sost);
      } else {
        led2_sost = 0;
        digitalWrite(led2, led2_sost);
      }
    }
    if (subscription == &room3)    {
      if (!strcmp((char*) room3.lastread, "ON"))      {
        led3_sost = 1;
        digitalWrite(led3, led3_sost);
      } else {
        led3_sost = 0;
        digitalWrite(led3, led3_sost);
      }
    }
    if (subscription == &lamp)    {//если значение на канале обновилось
      if (!strcmp((char*) lamp.lastread, "ON"))      {
        Lamp_mode = 1;

      } else {
        Lamp_mode = 2;
      }
    }
  }

}



void MQTT_connect() {
  if (mqtt.connected())  {//если уже подключены
    retries = 3;//обнуляем значение ошибок
    return;//выходим
  }



  if ((ret = mqtt.connect()) != 0 ) { //если не удалось подключиться                                                   // connect will return 0 for connected вместо if было while
    mqtt.disconnect();
    retries--;
  }

}


void getTemperature() {
  h = dht.readHumidity() ;//считываем показания влажности
  temp_C = dht.readTemperature() ; //считываем показания температуры
  if (isnan(h) || isnan(temp_C)) {//если значение неверное
    temp_C = 0;//температуру устанавливаем в 0
    h = 0;//влажность устанавливаем в 0
    return;//возвращаемся в предыдущее место кода
  }

}
