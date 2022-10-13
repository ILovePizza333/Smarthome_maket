void temp() {//функция проверки температуры и влажности
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t) ) {
    klimat = "Ошибка снятия температуры и влажности";
    return;
  }
  klimat = "Влажность на улице:" + String(h) + "%  Температура: " + String(t) + "°C ";
}
