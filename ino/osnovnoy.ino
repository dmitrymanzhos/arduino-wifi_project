/// esp+arduino
// отправлялка данных с градусника dht11 на народмон.ру 
// для отладки и демонстрации работы, не является готовым проектом!.

// #include <dht11.h>

#include <stdio.h>
#include <SoftwareSerial.h> // если UNO
SoftwareSerial esp(2, 3);
 
// #define esp Serial1 // меняем Serial1, на esp, ибо serial может быть софтовый

#define DHT11PIN 11  // пин DHT11

// dht11 DHT11;
 
// void narodmonSend(){  
//   DHT11.read(DHT11PIN); // читаем данные с градусника

//     // массив в котором будем формировать пакет для отправки
//     // размер массива должен быть равен размеру пакета
//     // если больше, есп нечего не отправит, если меньше, отправит не всё
//   char val[48]; 

//     // собераем пакет для отправки
//   snprintf(val, sizeof(val), "#FFFFFFFFFFFF#ardESP\n#H1DHT11#%d\n#T1DHT11#%d\n##",
//           DHT11.humidity, DHT11.temperature);

//     // отправляем пакет
//   esp.println("AT+CIPSTART=\"TCP\",\"narodmon.ru\",8283"); // соединяемся с сервером
//   delay(1);
//       if (esp.find("Linked")){                             // если соединились
//         esp.print("AT+CIPSEND=");                          // даем команду на отправку
//         esp.println(sizeof(val));                          // и длину пакета
//         delay(10);                                         // ждем
//         esp.println(val);                                  // и отпраляем пакет
//       }
//       else Serial.print("connect failed.");                // иначе отписываемся о неудачи
   
// }  
///////////

void setup() {
  Serial.begin(115200); // Serial monitor
  esp.begin(115200); // ESP8266
 
  // while (!Serial); // wait for serial port to connect. Needed for Leonardo only
  esp.println("AT+RST");
  esp.println("AT");
  while (esp.available()) { // смотрим что ответил есп после отправки
    Serial.write(esp.read()); 
  }
  esp.println("AT+CWMODE=1");     // делаем есп клиентом  
  
  // Serial.write((char)esp.read());
  // while (esp.available() > 0) { // смотрим что ответил есп после отправки
    
  //   Serial.write(esp.read()); 
  // }
  esp.println("AT+RST"); // сбрасываем есп   
  delay(500);   
  esp.println("AT+CWJAP=\"Pppppp\",\"2444666668888888\""); // подключение к сети

  esp.println("AT+CIPMUX=0");     // выключаем режим множественных подключений  
  
  esp.flush();

  while(1){                       // ждем подключение к сети
    esp.println("AT+CWJAP?");     // спрашиваем состояние
    // while (esp.available() > 0){
      // Serial.write(esp.read());
    if (esp.find("OK")) break;  // если в ответе на команду нашли OK, выходим из цикла
    else {
      Serial.print("-");
      Serial.print(esp.read());
    }
    delay(250);    
  }

  Serial.println("GOOOAL");

  while(1){                       // ждем пока выдадут IP
    esp.println("AT+CIFSR");       // спрашиваем состояние
    if (esp.find("192")) break;  // если нам дали IP, выходим из цикла
    else Serial.print("net");
    delay(250);    
  }
  
  esp.flush();
  
  // narodmonSend(); // отправляем данные
 
}
 

void loop() {
  esp.println("AT+CIPSTART=\"TCP\",\"192.168.43.1\",443");
  esp.println("AT+CIPSEND=0,124");
  esp.println("write 10.20.30.40 5.623");
  delay(1000);
  while (esp.available() > 0) { // смотрим что ответил есп после отправки
    Serial.write(esp.read());
    // Serial.println("printed\n"); 
  }

}
