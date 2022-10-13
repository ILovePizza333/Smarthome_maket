void uart() {//функция обработки uart
  while (Serial.available() > 0 && m != ';') {
    m = Serial.read();
    msg += m;
  }
  if (((!Serial.available() || Serial.available() <= 0) && msg != " ") || m == ';') {
    msg.trim();
    if (msg.indexOf("RESET") != -1 ) {
      resetFunc();
    }
    if (msg.indexOf("lamp?") != -1) {
           Serial.println("lamp" + String(Lamp_mode) + ";");
    }
    if (msg.indexOf("GARAGE?") != -1) {
      String G_A = GARAGE_sost;
      if (garage_auto == 1) G_A += "AUTO;";
      if (garage_auto == 0)G_A += "AOFF;";
      Serial.println(G_A);
    }

    if (msg.indexOf("DOOR?") != -1) {
      // Serial.print(DOOR_sost );
      String D_A = DOOR_sost;
      if (home_auto == 1) D_A += "AUTO;";
      if (home_auto == 0)D_A += "AOFF;";
      Serial.println(D_A);
    }
    if (msg.indexOf("hum?") != -1) {
      Serial.println("hum" + String(h) + ";");
    }
    if (msg.indexOf("temp?") != -1) {
      Serial.println("temp" + String(t) + ";");
    }
    if (msg.indexOf("ok?") != -1) {
      if (msg.indexOf("DOOR_OPEN") != -1 ) {
        home_auto = 0;
        u = code_home;
        DOOR_sost = "DOOR_OPEN";
        timeLast_home = millis();
      }
      if (msg.indexOf("DOOR_CLOSE") != -1 ) {
        home_auto = 0;
        u = "";
        DOOR_sost = "DOOR_CLOSE";
        timeLast_home = millis() - 10000;
      }
      if (msg.indexOf("GARAGE_CLOSE") != -1 ) {
        garage_auto = 0;
        u2 = "";
        GARAGE_sost = "GARAGE_CLOSE";
        timeLast_garage = millis() - 10000;
      }
      if (msg.indexOf("GARAGE_OPEN") != -1 ) {
        garage_auto = 0;
        u2 = code_garage;
        GARAGE_sost = "GARAGE_OPEN";
        timeLast_garage = millis();
      }
      if (msg.indexOf("DOOR_AUTO") != -1 ) {
        home_auto = 1;
      }
      if (msg.indexOf("GARAGE_AUTO") != -1 ) {
        garage_auto = 1;
      }
      if (msg.indexOf("LAMP=1") != -1 ) {
        Lamp_mode = 1;
      }
      if (msg.indexOf("LAMP=0") != -1 ) {
        Lamp_mode = 0;
      }

      if (msg.indexOf("LAMP=2") != -1 ) {
        Lamp_mode = 2;
      }
      Serial.println("ok!;");
      /*   delay(1);
         Serial.println(DOOR_sost);
         delay(1);
         Serial.println(GARAGE_sost);
         delay(1);
         if (garage_auto == 1)Serial.println("GARAGE_AUTO");
         delay(1);
         if (home_auto == 1)Serial.println("DOOR_AUTO");
         delay(30);*/
    }
    msg = " ";
    m = ' ';
  }
}
