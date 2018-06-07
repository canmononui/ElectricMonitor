/*
  Web client

This sketch connects to a website (http://www.google.com)
using an Arduino Wiznet Ethernet shield. 

Circuit:
* Ethernet shield attached to pins 10, 11, 12, 13

created 18 Dec 2009
by David A. Mellis
modified 9 Apr 2012
by Tom Igoe, based on work by Adrian McEwen

*/

#include <SPI.h>
#include <Ethernet.h>

#include "DHT.h"
#define DHTPIN 22
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "xxx.com";    // name address for Google (using DNS)


IPAddress ip(192,168,1,109);


int temp;
int moi;

EthernetClient client;

void setup() {
// Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server,80)) {
    Serial.println("connected");
    // Make a HTTP request:
    temp = dht.readTemperature();//dht11
    moi = analogRead(15); //soil moisture
    Serial.println(temp);
    Serial.println(moi);
    Serial.print("server name : ");
    Serial.println(server);
    client.print( "GET /add.php?"); // php??
   client.print("temp1=");
   //client.print(tempValue);
   client.print(temp);
   client.print("&&");
   client.print("moi1=");
   //client.print(levelValue);
   client.print(moi);
   client.println( " HTTP/1.1");
   client.println( "Host: xxx.com" );//ur web server
   client.println( "Content-Type: application/x-www-form-urlencoded" );
   client.println( "Connection: close" );
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();     //<< read data mysql
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while(true);
  }
}
