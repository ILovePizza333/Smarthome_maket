void card_garage() {//функция проверки метки автомобиля и открытия/закрытия ворот
  if (curTime - timeLast_garage  > 10000 && u2 != "0") {
    u2 = "0";
    GARAGE_sost = "GARAGE_CLOSE";
    garage_servo.write(110);
  garage_servo2.write(0);
    flag_garage = 0;
  }
  if ((u2 == code_garage || u2 == code_key) && flag_garage == 0) {
    GARAGE_sost = "GARAGE_OPEN";
    garage_servo.write(0);
  garage_servo2.write(110);
    flag_garage = 1;
  }
  if ((u2 != code_garage && u2 != code_key) && u2 != "0") {
  GARAGE_sost = "GARAGE_CLOSE";
  garage_servo.write(110);
  garage_servo2.write(0);
    flag_garage = 0;
  }

  if ( ! garage_card.PICC_IsNewCardPresent())    return;  
      if ( ! garage_card.PICC_ReadCardSerial())    return; 
        dump_byte_array2(garage_card.uid.uidByte, garage_card.uid.size);
        
  }
