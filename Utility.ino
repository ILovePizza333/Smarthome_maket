void dump_byte_array(byte *buffer, byte bufferSize) {//функция считывания домашней RFID метки
  u = "";
  for (byte i = 0; i < bufferSize; i++) {
    u += buffer[i];
    timeLast_home = millis();
  }
}



void dump_byte_array2(byte *buffer, byte bufferSize) {//функция считывания  RFID метки автомобиля
  u2 = "";
  for (byte i = 0; i < bufferSize; i++) {
    u2 += buffer[i];
    timeLast_garage = millis();
    
  }
}

void(* resetFunc)(void)=0;//функция перезагрузки ардуино
