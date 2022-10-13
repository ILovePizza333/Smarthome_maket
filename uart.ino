void uart() {
  current_time = millis();//присваем переменной время работы мк со старта
  t = Timer * 1000;//переменная для времени обновления
  if (current_time - start_time >= t ) {
    //если время сейчас больше чем в прошлый раз больше чем на минуту
    // getTemperature();//обновлям температуру
    start_time = millis();//сбрасываем счетчик
    //формируем сообщение со значениями переменных для отправки в прдуино нано
    chek_msg = "ok?LAMP=";
    chek_msg += Lamp_mode;
    if (DOOR_AUTO == "background: #FFD700;") {
      chek_msg += "DOOR_AUTO";
    } else {
      if (DOOR == "background: #FFD700;") {
        chek_msg += "DOOR_OPEN";
      } else {
        chek_msg += "DOOR_CLOSE";
      }
    }
    if (GARAGE_AUTO == "background: #FFD700;") {
      chek_msg += "GARAGE_AUTO";
    } else {
      if (GARAGE == "background: #FFD700;") {
        chek_msg += "GARAGE_OPEN";
      } else {
        chek_msg += "GARAGE_CLOSE";
      }
    }
    chek_msg += ";";
    // Serial.println("ok?");//проверяем подключена ли ардуино нано
    Serial.println(chek_msg);//отправляем в ардуино значение переменных
  }

  while (Serial.available() > 0) {//пока сериал порт активен
    char m = Serial.read();//считываем данные
    msg += m;//записываем в строковую переменную
  }
  if (!Serial.available() && msg.indexOf(";") != -1) {//если мериал порт неактивен разбираем полученное сообщение
    msg.trim();//убираем лишние пробелы в начале и в конце сообщения
    Serial.print("msg; ");      Serial.println(msg);

    if (msg.indexOf("lamp") != -1) {
      // Serial.print("float: ");      Serial.println(msg.toFloat());
      msg = msg.substring(4, msg.length() - 1);
      int la = msg.toFloat();
      if (la = 1) SVET = "background: #FFD700;"; SVET_AUTO = "";
      if (la = 0) SVET = ""; SVET_AUTO = "";
      if (la = 2) SVET_AUTO = "background: #FFD700;";
      //Serial.println("DOOR?");
    }

    if (msg.indexOf("GARAGE") != -1) {
      // Serial.print("float: ");      Serial.println(msg.toFloat());
      if (msg.indexOf("OPEN") != -1) {
        GARAGE = "background: #FFD700;";
      }
      if (msg.indexOf("CLOSE") != -1) {
        GARAGE = "";
      }
      if (msg.indexOf("AUTO") != -1) {
        GARAGE_AUTO = "background: #FFD700;";
      }
      if (msg.indexOf("AOFF") != -1) {
        GARAGE_AUTO = "";
      }
      Serial.println("lamp?");
    }

    if (msg.indexOf("DOOR") != -1) {
      // Serial.print("float: ");      Serial.println(msg.toFloat());
      if (msg.indexOf("OPEN") != -1) {
        DOOR = "background: #FFD700;";
      }
      if (msg.indexOf("CLOSE") != -1) {
        DOOR = "";
      }
      if (msg.indexOf("AUTO") != -1) {
        DOOR_AUTO = "background: #FFD700;";
      }
      if (msg.indexOf("AOFF") != -1) {
        DOOR_AUTO = "";
      }
      Serial.println("GARAGE?");
    }
    if (msg.indexOf("hum") != -1) {
      // Serial.print("float: ");      Serial.println(msg.toFloat());
      msg = msg.substring(3, msg.length() - 1);
      h_o = msg.toFloat();
      Serial.println("DOOR?");
    }
    if (msg.indexOf("temp") != -1) {
      // Serial.print("float: ");      Serial.println(msg.toFloat());
      msg = msg.substring(4, msg.length() - 1);
      t_o = msg.toFloat();
      Serial.println("hum?");
    }

    if (msg.indexOf("ok!") != -1) {//если в сообщении найдена строка
      Serial.println("temp?");
      error_time = millis();//сбрасываем счетчик времени ошибки
      Nano_Errors = 0;//сбрасываем количество ошибок
    } else {
      current_time = millis();//присваем переменной время работы мк со старта
      if (current_time - error_time >= 5000 ) {
        //если время сейчас больше чем в прошлый раз больше чем на 5 секунд
        error_time = millis();//сбрасываем счетчик времени ошибок
        Nano_Errors++;//прибавляем единицу к переменной ошибок

      }
    }
    msg = " "; //обнуляем переменную входящего сообщения
  }
}
