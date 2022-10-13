void lamp() {//функция включения фонаря и автоматической регулировки 
  if(Lamp_mode==2){
  Light = analogRead(Light_sensor);
  if (digitalRead(Motion_sensor) == HIGH && Light <= Light_point) {
    digitalWrite(Lamp, HIGH);  
    last_motion = millis();
  } else {
    curTime = millis();
    if (curTime - last_motion >= time_motion && last_motion!=-1) {
      digitalWrite(Lamp, LOW); 
      last_motion=-1;
    }

  }
  }
  if(Lamp_mode==1){
    digitalWrite(Lamp, HIGH);
  }
    if(Lamp_mode==0){
    digitalWrite(Lamp, LOW);
  }
}
