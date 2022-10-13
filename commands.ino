void command() {
  server.on("/", []() {//если отправлен запрос на главную страницу сайта
    web();//обновляем сайт
    server.send(200, "text/html", webPage);//отвечаем клиенту
  });

  server.on("/SVET", []() {//если отправлен запрос на адрес http://192.168.43.94/SVET/
    //меняем режим фонаря
    if (Lamp_mode == 1) {
      Lamp_mode = 0;
    } else if (Lamp_mode == 0 || Lamp_mode == 2) {
      Lamp_mode = 1;
    }
    web();//обновляем страницу
    server.send(200, "text/html", webPage);//отвечаем клиенту

  });

  server.on("/AUTO", []() {//если отправлен запрос на адрес http://192.168.43.94/SVET/
    Lamp_mode = 2;//присваем лампе режим 2
    web();//обновляем сайт
    server.send(200, "text/html", webPage);//отвечаем клиенту
  });

  server.on("/DOOR", []() {
    DOOR_AUTO = "";
    if (DOOR == "background: #FFD700;") {
      DOOR = "";
    } else {
      DOOR = "background: #FFD700;";
    }
    web();
    server.send(200, "text/html", webPage);
    pub = 9; //прибавляем значение к переменной, чобы в следующий опубликовать другую
    MQTT_Publish();//публикуем одно из текущих значений переменных
    last_time_publish = millis();//сбрасываем счетчик
  });
  server.on("/GARAGE", []() {
    GARAGE_AUTO = "";
    if (GARAGE == "background: #FFD700;") {
      GARAGE = "";
    } else {
      GARAGE = "background: #FFD700;";
    }
    web();
    server.send(200, "text/html", webPage);
    pub = 10; //прибавляем значение к переменной, чобы в следующий опубликовать другую
    MQTT_Publish();//публикуем одно из текущих значений переменных
    last_time_publish = millis();//сбрасываем счетчик
  });
  server.on("/DOOR_AUTO", []() {
    if ( DOOR_AUTO == "background: #FFD700;") {
      DOOR_AUTO = "";
    } else {
      DOOR_AUTO = "background: #FFD700;";
    }
    web();
    server.send(200, "text/html", webPage);

  });
  server.on("/GARAGE_AUTO", []() {
    if (GARAGE_AUTO == "background: #FFD700;") {
      GARAGE_AUTO = "";
    } else {
      GARAGE_AUTO = "background: #FFD700;";
    }
    web();
    server.send(200, "text/html", webPage);

  });
  server.on("/ROOM1", []() {
    led_sost = !led_sost;
    web();
    server.send(200, "text/html", webPage);
    digitalWrite(led, led_sost);
    pub = 5; //прибавляем значение к переменной, чобы в следующий опубликовать другую
    MQTT_Publish();//публикуем одно из текущих значений переменных
    last_time_publish = millis();//сбрасываем счетчик

  });
  server.on("/ROOM2", []() {
    led2_sost = !led2_sost;
    web();
    server.send(200, "text/html", webPage);
    digitalWrite(led2, led2_sost);
    pub = 6; //прибавляем значение к переменной, чобы в следующий опубликовать другую
    MQTT_Publish();//публикуем одно из текущих значений переменных
    last_time_publish = millis();//сбрасываем счетчик
  });
  server.on("/ROOM3", []() {
    led3_sost = !led3_sost;
    web();
    server.send(200, "text/html", webPage);
    digitalWrite(led3, led3_sost);
    pub = 7; //прибавляем значение к переменной, чобы в следующий опубликовать другую
    MQTT_Publish();//публикуем одно из текущих значений переменных
    last_time_publish = millis();//сбрасываем счетчик
  });

  server.on("/UPDATE", []() {
    web();
    getTemperature();
    server.send(200, "text/html", webPage);

  });


  server.on("/RESET", []() {
    Serial.println("RESET");
    web();
    server.send(200, "text/html", webPage);
    delay(100);
    ESP.restart();
  });
  server.begin();//старт сервера

}
