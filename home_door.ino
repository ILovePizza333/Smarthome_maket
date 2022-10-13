void card_home() {//функция проверки метки автомобиля и открытия/закрытия ворот
  if (curTime - timeLast_home  > 10000 && u != "0") {
    u = "0";
    DOOR_sost = "DOOR_CLOSE";
    home_servo.write(90); 
  }
  if (u == code_home || u == code_key) {
    DOOR_sost = "DOOR_OPEN";
    home_servo.write(0);
  }
  if ((u != code_home && u != code_key ) && u != "0") {
    DOOR_sost = "DOOR_CLOSE";
    home_servo.write(90);  
  }
  if ( ! mfrc522.PICC_IsNewCardPresent())    return;
  if ( ! mfrc522.PICC_ReadCardSerial())    return;
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  }
