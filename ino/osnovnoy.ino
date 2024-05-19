/// esp+arduino
// отправлялка данных с градусника dht11 на народмон.ру 
// для отладки и демонстрации работы, не является готовым проектом!.

// #include <dht11.h>

#include <stdio.h>
#include <SoftwareSerial.h> // если UNO

#define frequency 115200

#define SSID  "Pppppp"
#define PSW "2444666668888888"

#define SERVER_IP "192.168.43.214"
#define SERVER_PORT 7000
#define ESP_PORT 7001

#define BUFFER_SIZE 512
char buffer[BUFFER_SIZE];

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

//void do_command(char* command){
//  while(1){
//    esp.println(command);
//    if (esp.find("OK")) break;
//    else Serial.println("err");
//    delay(100);
//  }
//  return;
//}



void setup() {
  Serial.begin(frequency); // Serial monitor
  esp.begin(frequency); // ESP8266
  
  clearSerialBuffer();
  Serial.println(GetResponse("AT+RST",3400));

  Serial.println(GetResponse("AT+CWMODE=3",300));
  connectWiFi();
  // Serial.println(GetResponse("AT+CIPMUX=0",300));
  // while (!Serial); // wait for serial port to connect. Needed for Leonardo only
  // esp.println("AT+RST");
  // esp.println("AT");
  // while (esp.available()) { // смотрим что ответил есп после отправки
  //   Serial.write(esp.read()); 
  // }
  // esp.println("AT+CWMODE=3");     // делаем есп клиентом  
  
  // Serial.write((char)esp.read());
  // while (esp.available() > 0) { // смотрим что ответил есп после отправки
    
  //   Serial.write(esp.read()); 
  // }
//   esp.println("AT+RST"); // сбрасываем есп   
//   delay(500);   
//   esp.println("AT+CWJAP=SSID,PWD); // подключение к сети
// //  esp.println("AT+CWJAP=\"&Dolgopniki\",\"KSP_kr0t0vuxa\"");

//   esp.println("AT+CIPMUX=0");     // выключаем режим множественных подключений  
  
//   esp.flush();
//
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
//  do_command("AT+CWJAP?");
  
  Serial.println("GOOOAL");

  while(1){                       // ждем пока выдадут IP
    esp.println("AT+CIFSR");       // спрашиваем состояние
    // break;
    if (esp.find("192")) break;  // если нам дали IP, выходим из цикла
    else Serial.print("net");
    delay(250);    
  }
  
  esp.flush();
  
  // narodmonSend(); // отправляем данные
 
}
 

void loop() {
  delay(300);
  while(1){
    esp.println("AT+CIPSTART=\"UDP\",\"192.168.43.214\",7000,7001,0");
    delay(100);
    if (esp.find("CON")){
      Serial.println("goooal");
      break;
    }
    else Serial.println("err");
  }
//  esp.println("AT+CIPSTART=\"UDP\",\"192.168.43.1\",7000,7001,0");
//  esp.println("AT+CIPSTART=\"TCP\",\"192.168.43.1\",7000,7000,0");
//  do_command("AT+CIPSTART=\"UDP\",\"192.168.43.1\",7000,7001,0");
  
//  delay(500);
//  esp.println("AT+CIPMODE=1");
//  delay(500);


  while(1){
    esp.println("AT+CIPSEND=25");
    delay(100);
    if (esp.find("OK")){
      Serial.println("goooal.1");
      break;
    }
    else Serial.println("err");
  }
//  esp.println("AT+CIPSEND=0,31");
//  do_command("AT+CIPSEND=0,31");


//  delay(500);
  while(1){
    esp.println("write 10.20.30.40 5.623");
    delay(100);
    if (esp.find("SEND")){
      clearSerialBuffer();
      Serial.println("goooal.2");
      break;
    }
    else {
      Serial.println("err");
      clearSerialBuffer();
      return loop();
    }
  }

//  esp.println("write 10.20.30.40 5.623");
//  delay(500);

  
//   esp.println("AT+CIPMODE=0");
//   delay(500);

//    while(1){
//    esp.println("AT+CIPCLOSE");
//    delay(100);
//    if (esp.find("CLOSED")){
//      Serial.println("goooal.3");
//      break;
//    }
//    else Serial.println("err");
//  }
  
//  esp.println("AT+CIPCLOSE");
  delay(500);
  
  Serial.println("sent\n");
  while (esp.available() > 0) { // смотрим что ответил есп после отправки
    Serial.write(esp.read());
//     Serial.println("printed\n"); 
  }
  delay(1000);
}

/////////////////////отправка АТ-команд/////////////////////
String GetResponse(String AT_Command, int wait)
{
  String tmpData;
  
  esp.println(AT_Command);
  delay(wait);
  while (esp.available() >0 )  
   {
    char c = esp.read();
    tmpData += c;
    
    // if ( tmpData.indexOf(AT_Command) > -1 )         
    //   tmpData = "";
    // else
    //   tmpData.trim();       
          
   }
  return tmpData;
}

////////////////////подключение к wifi/////////////////////        
boolean connectWiFi() 
{
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PSW;
  cmd += "\"";
  Serial.println(cmd); 
  Serial.println(GetResponse(cmd,6500));
}

//////////////////////очистка esp////////////////////
void clearSerialBuffer(void) 
{
       while ( esp.available() > 0 ) 
       {
         esp.read();
       }
}

////////////////////очистка буфера//////////////////////// 
void clearBuffer(void) {
       for (int i =0;i<BUFFER_SIZE;i++ ) 
       {
         buffer[i]=0;
       }
}