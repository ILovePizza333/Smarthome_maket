void web() {
  //проверяем состояние переменных, присваеваем кнопкам цвета
  if (led_sost == 1) {
    ROOM1 = "background: #FFD700;";
  } else {
    ROOM1 = "";
  }
  if (led2_sost == 1) {
    ROOM2 = "background: #FFD700;";
  } else {
    ROOM2 = "";
  }
  if (led3_sost == 1) {
    ROOM3 = "background: #FFD700;";
  } else {
    ROOM3 = "";
  }
  if (Lamp_mode == 2) {
    SVET = "";
    SVET_AUTO = "background: #FFD700;";
  } else if (Lamp_mode == 1) {
    SVET = "background: #FFD700;";
    SVET_AUTO = "";
  } else if (Lamp_mode == 0) {
    SVET = "";
    SVET_AUTO = "";
  }

  webPage = "";//обнуляем значение переменной

  webPage += "<html>";//начало html кода
  webPage += "<head>";//прописываем "шапку" сайта
  webPage += "<title>Добро пожаловать!</title>";//заголовок в поисковой строке
  webPage += "<meta http-equiv='Content-Type' content ='text/html; charset=utf-8'>";//устанавливаем тип контента, кодировку
  webPage += "<meta http-equiv='Refresh' content='5;http://";
  webPage += ip.toString();
  Serial.println(ip.toString());
  webPage += "/UPDATE'>";//каждые 5 секунд обновляем страницу
  webPage += "</head>";//конец "шапки"

  webPage += "<body style = 'background-color: #a6b2c3'>";//фоновый цвет
  webPage += "<h1 style='color: #000000' align = center >Умный дом </h1>";//Первая стока
  webPage += "<style> p {margin-top: 2em;    margin-bottom: 1em;}</style>";//установка шрифта
  if (Nano_Errors >= 5) {//если количество неудачных подключений к ардуино нано больше 5
    //Выводим надпись "Уличный контроллер недоступен"
    webPage += "<p align = center><font size='5' color='red' >Уличный контроллер недоступен!</font></p>";
  }

  if (retries <= 0)  {//если количество попыток подключения к MQTT серверу
    //Выводим надпись "MQTT недоступен!"
    webPage += "<p align = center><font size='5' color='red' >MQTT недоступен!</font></p>";
  }
  webPage += "<p align = center><font size='5' >Уличный фонарь:</font></p><p align = center> <a href=\"SVET\"><button style='width:200px;height:100px;";
  //создаем кнопку включения\выключения фонаря
  webPage += SVET;//задаем ей заранее выбранный цвет
  webPage += "'><big><big><big>Свет</big></big></big></button></a>&nbsp;";

  webPage += " <a href=\"AUTO\"><button style='width:200px;height:100px;";//кнопка включения/отключения автоматического режима
  webPage += SVET_AUTO;
  webPage += "'><big><big><big>Автомат</big></big></big></button></a>&nbsp;</p>";

  webPage += "<p align = center><a href=\"ROOM1\"><button style='width:200px;height:100px;";//
  webPage += ROOM1;
  webPage += "'><big><big><big>1 этаж</big></big></big></button></a>";

  webPage += "<a href=\"ROOM2\"><button style='width:200px;height:100px;";
  webPage += ROOM2;
  webPage += "'><big><big><big>2 этаж</big></big></big></button></a>&nbsp;";

  webPage += "<a href=\"ROOM3\"><button style='width:200px;height:100px;";
  webPage += ROOM3;
  webPage += "'><big><big><big>балкон</big></big></big></button></a>&nbsp;";


  webPage += "<p align = center><a href=\"DOOR\"><button style='width:200px;height:100px;";
  webPage += DOOR;
  webPage += "'><big><big><big>дверь дома</big></big></big></button></a>&nbsp;";
  webPage += " <a href=\"DOOR_AUTO\"><button style='width:200px;height:100px;";
  webPage += DOOR_AUTO;
  webPage += "'><big><big><big>Автомат</big></big></big></button></a>&nbsp;</p>";

  webPage += "<p align = center><a href=\"GARAGE\"><button style='width:200px;height:100px;";
  webPage += GARAGE;
  webPage += "'><big><big><big>дверь гаража</big></big></big></button></a>&nbsp;";
  webPage += " <a href=\"GARAGE_AUTO\"><button style='width:200px;height:100px;";
  webPage += GARAGE_AUTO;
  webPage += "'><big><big><big>Автомат</big></big></big></button></a>&nbsp;</p>";


  //вывод температуры и влажности
  webPage += "<p align = center>Температура в комнате: ";
  webPage += temp_C;
  webPage += "</p>";

  webPage += "<p align = center>Влажность в комнате: ";
  webPage += h;
  webPage += "</p>";

  webPage += "<p align = center>Температура на улице: ";
  webPage += t_o;
  webPage += "</p>";

  webPage += "<p align = center>Влажность на улице: ";
  webPage += h_o;
  webPage += "</p>";


  webPage += "<p align = center><a href=\"UPDATE\"><button style='width:100px;height:100px'>Обновить</button></a>&nbsp;</p>";//кнопка обновления страницы

  webPage += "<p align = center><a href=\"RESET\"><button style='width:100px;height:100px'>Перезагрузка</button></a>&nbsp;</p>";//кнопка перезагрузки

  webPage += "</body>";//конец "тела" сайта

  webPage += "</html>";//конец html страницы
}
