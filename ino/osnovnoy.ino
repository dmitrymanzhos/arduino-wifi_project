/// прошивка для esp+arduino

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11 - датчик температуры
#define DHT11PIN 11  // пин DHT11


#include <stdio.h>
#include <SoftwareSerial.h> // Serial для esp


#define frequency 115200
#define SSID  "Pppppp"
#define PSW "2444666668888888"
#define SERVER_IP "192.168.43.214"
#define SERVER_PORT "7000"
#define ESP_PORT "7001"
#define BUFFER_SIZE 512
char buffer[BUFFER_SIZE];

int my_time = 100;  


SoftwareSerial esp(2, 3);
DHT dht(DHT11PIN, DHTTYPE);



void setup() {
  Serial.begin(frequency); // Serial monitor
  esp.begin(frequency); // ESP8266
  dht.begin(); // DHT11


  clearSerialBuffer();
  Serial.println(GetResponse("AT+RST", "OK", "RESET", 30, 0));
  Serial.println(GetResponse("AT+CWMODE=3", "OK", "CONNECTION_MODE", 30, 0));
  
  connectWiFi();

  // Serial.println(GetResponse("AT+CIPMUX=0",300, 0));
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
//   delay(500, 0);   
//   esp.println("AT+CWJAP=SSID,PWD); // подключение к сети

//   esp.println("AT+CIPMUX=0");     // выключаем режим множественных подключений  
  
//   esp.flush();
//
//   while(1){                       // ждем подключение к сети
//     esp.println("AT+CWJAP?");     // спрашиваем состояние
//     // while (esp.available() > 0){
//       // Serial.write(esp.read());
    
//     if (esp.find("OK")) break;  // если в ответе на команду нашли OK, выходим из цикла
//     else {
//       Serial.print("-");
//       Serial.print(esp.read());
//     }
//     delay(250);    
//   }
// //  do_command("AT+CWJAP?");
  
//   Serial.println("GOOOAL");

//   while(1){                       // ждем пока выдадут IP
//     esp.println("AT+CIFSR");       // спрашиваем состояние
//     // break;
//     if (esp.find("192")) break;  // если нам дали IP, выходим из цикла
//     else Serial.print("net");
//     delay(250);    
//   }
  
//   esp.flush();
  
  // narodmonSend(); // отправляем данные
 
}
 

void loop() {
  delay(30);
  send_data("10", "20");
  // while(1){
  //   esp.println("AT+CIPSTART=\"UDP\",\"192.168.43.214\",7000,7001,0");
  //   delay(100, 0);
  //   if (esp.find("CON")){
  //     Serial.println("goooal");
  //     break;
  //   }
  //   else Serial.println("err");
  // }
//  esp.println("AT+CIPSTART=\"UDP\",\"192.168.43.1\",7000,7001,0");
//  esp.println("AT+CIPSTART=\"TCP\",\"192.168.43.1\",7000,7000,0");
//  do_command("AT+CIPSTART=\"UDP\",\"192.168.43.1\",7000,7001,0");
  
//  delay(500, 0);
//  esp.println("AT+CIPMODE=1");
//  delay(500, 0);


  // while(1){
  //   esp.println("AT+CIPSEND=25");
  //   delay(100, 0);
  //   if (esp.find("OK")){
  //     Serial.println("goooal.1");
  //     break;
  //   }
  //   else Serial.println("err");
  // }
//  esp.println("AT+CIPSEND=0,31");
//  do_command("AT+CIPSEND=0,31");


//  delay(500, 0);
  // while(1){
  //   esp.println("write 10.20.30.40 5.623");
  //   delay(100, 0);
  //   if (esp.find("SEND")){
  //     clearSerialBuffer();
  //     Serial.println("goooal.2");
  //     break;
  //   }
  //   else {
  //     Serial.println("err");
  //     clearSerialBuffer();
  //     return loop();
  //   }
  // }

//  esp.println("write 10.20.30.40 5.623");
//  delay(500, 0);

  
//   esp.println("AT+CIPMODE=0");
//   delay(500, 0);

//    while(1){
//    esp.println("AT+CIPCLOSE");
//    delay(100, 0);
//    if (esp.find("CLOSED")){
//      Serial.println("goooal.3");
//      break;
//    }
//    else Serial.println("err");
//  }
  
//  esp.println("AT+CIPCLOSE");
//   delay(500, 0);
  
//   Serial.println("sent\n");
//   while (esp.available() > 0) { // смотрим что ответил есп после отправки
//     Serial.write(esp.read());
// //     Serial.println("printed\n"); 
//   }
  delay(100);
}

//отправка АТ-команд
String GetResponse(String AT_Command, char response[], String answer, int wait, int flag)
{
  while(1) {
    clearSerialBuffer();
    esp.println(AT_Command);
    delay(wait);

    if (esp.find(response)){
      return answer;
    }
      else {
        Serial.println("err");
        if (flag==1) return "err";
      }
  }
}

//отправка данных
void send_data(String time, String data){

  String cmd = "AT+CIPSTART=\"UDP\",\"";
  cmd += SERVER_IP;
  cmd += "\",";
  cmd += SERVER_PORT;
  cmd += ",";
  cmd += ESP_PORT;
  cmd += ",0";

  Serial.println(GetResponse(cmd, "CON", "CONNECTION_OPENED", 10, 0));

  Serial.println(GetResponse("AT+CIPSEND=16", "OK", "READY", 20, 0));

  my_time += 1;
  Serial.println(dht.readTemperature());
  Serial.println(my_time);
  String t = (String) dht.readTemperature();
  cmd = "write ";
  cmd += String(my_time);
  cmd += " ";
  cmd += t;
  Serial.println(cmd);
  
  // while (1){
  clearSerialBuffer();
  if ((GetResponse(cmd, "OK", "SEND", 10, 1)) == "err" && (GetResponse(cmd, "OK", "SEND", 10, 1)) == "err") {
    esp.println(".................................................");
    delay(500);
    clearSerialBuffer();
//    GetResponse("AT+CIPCLOSE", "OK", "CLOSED", 100, 0);
    return setup();
//    return send_data(time, data);
  }
  else Serial.println("SUCCESS");
    // if (GetResponse(cmd, "OK", "READY", 100, 0) == String("READY")) return Serial.println("send");
    // else{
    //   Serial.println("err");
    //   return send_data(time, data);
    // }
  // }
  esp.println(".................................................");
  delay(10);
  clearSerialBuffer();
//  Serial.println(GetResponse("AT+CIPCLOSE", "OK", "CLOSED", 100, 0));
  //    esp.println("AT+CIPCLOSE");
  //  delay(100, 0);
  //  if (esp.find("CLOSED")){
  //    Serial.println("goooal.3");
  //    break;
  //  }
  // Serial.println(GetResponse(cmd, "SEND", "READY", 100, 0));
  //   while(1){
  //   esp.println("write 10.20.30.40 5.623");
  //   delay(100, 0);
  //   if (esp.find("SEND")){
  //     clearSerialBuffer();
  //     Serial.println("goooal.2");
  //     break;
  //   }
  //   else {
  //     Serial.println("err");
  //     clearSerialBuffer();
  //     return loop();
  //   }
  // }
  // Serial.println("goooal");
  //   while(1){
  //   esp.println("AT+CIPSEND=25");
  //   delay(100, 0);
  //   if (esp.find("OK")){
  //     Serial.println("goooal.1");
  //     break;
  //   }
  //   else Serial.println("err");
  // }

  // while(1){
  //   esp.println("AT+CIPSTART=\"UDP\",\"192.168.43.214\",7000,7001,0");
  //   delay(100, 0);
  //   if (esp.find("CON")){
  //     Serial.println("goooal");
  //     break;
  //   }
  //   else Serial.println("err");
  // }

}

//подключение к wifi 
boolean connectWiFi() 
{
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PSW;
  cmd += "\"";
  // Serial.println(cmd); 
  Serial.println(GetResponse(cmd, "OK", "CONNECTED_WIFI", 50, 0));
}

//очистка esp
void clearSerialBuffer(void) 
{
       while ( esp.available() > 0 ) 
       {
         esp.read();
       }
}

//очистка буфера
void clearBuffer(void) {
       for (int i =0;i<BUFFER_SIZE;i++ ) 
       {
         buffer[i]=0;
       }
}