#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
unsigned char mac[] = { B8-08-CF-BF-10-C7 }; //Setting MAC Address

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float temperatureData;


char server[] = "192.168.1.105";
IPAddress ip(192,168,0,177); 
EthernetClient client; 

/* Setup for Ethernet and RFID */

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac, ip);
  }
  delay(1000);
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){
  temperatureData = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(30000); // interval
}


  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /shemama/recept?temperature=");
    client.print("GET /shemama/recept?temperature=");     //YOUR URL
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.1.105");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
