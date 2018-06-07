#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h> // Library Ethernet Shield
#include "EmonLib.h"  // Include Emon Library
EnergyMonitor emon1;  // Create an instance1
EnergyMonitor emon2;  // Create an instance2
EnergyMonitor emon3;  // Create an instance3
EnergyMonitor emon4;  // Create an instance4
EnergyMonitor emon5;  // Create an instance5
//VOLT
#define SAMPLING 300
#define VOFFSET  512 
#define ADC_PIN A0  //Connect sensor VOLT to port A0
#define AMPLITUDE 411.00
#define REAL_VAC  233.5 // Get the real VAC from voltmeter
String data="";         // Data POST to database
int adc_max,adc_min;
int adc_vpp;
int volt;               //Variable Volt
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;

void setup(){  
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
      Serial.println(F("Failed to configure Ethernet using DHCP")); //If can not connect to internet
      }
  Serial.println(Ethernet.localIP()); //Print IP in serial print
  // Current: input pin, calibration.
  emon1.current(1, 110); //amp_all Connect sensor to port A1
  emon2.current(2, 110); //amp_air Connect sensor to port A2
  emon3.current(3, 110); //amp_water Connect sensor to port A3
  emon4.current(4, 110); //amp_light Connect sensor to port A4
  emon5.current(5, 110); //amp_plug Connect sensor to port A5
  //calibration is explained bellow
}

void loop()
{
  //Get data from sensor
  volt=getvolt(); //Call funtion Getvolt
  double amp_all    = emon1.calcIrms(1480); //Call funtion calculator Irms 
  double amp_air    = emon2.calcIrms(1480); //Call funtion calculator Irms
  double amp_water  = emon3.calcIrms(1480); //Call funtion calculator Irms
  double amp_light  = emon4.calcIrms(1480); //Call funtion calculator Irms
  double amp_plug   = emon5.calcIrms(1480); //Call funtion calculator Irms
  //Print to serial print
  Serial.print(F("Power: "));
  Serial.println(amp_all*volt); 
  Serial.print(F("Volt: "));
  Serial.println(volt);          
  Serial.print(F("Amp_All: "));
  Serial.println(amp_all);
  Serial.print(F("Amp_Air: "));
  Serial.println(amp_air);
  Serial.print(F("Amp_Water: "));
  Serial.println(amp_water);
  Serial.print(F("Amp_Light: "));
  Serial.println(amp_light);
  Serial.print(F("Amp_Plug: "));
  Serial.println(amp_plug);
  
  //Gen data from Variable to link for POST to database
  data = "&volt1=" + String(volt) + "&amp_all1=" + String(amp_all) + "&amp_air1=" + String(amp_air) + "&amp_water1=" + String(amp_water) + "&amp_light1=" + String(amp_light) + "&amp_plug1=" + String(amp_plug);
  //data = "&V=" + String(volt) + "&A1=" + String(amp_all) + "&A2=" + String(amp_air) + "&A3=" + String(amp_water)+ "&A4=" + String(amp_light) + "&A5=" + String(amp_plug);
  Serial.println(data);
//  if (client.connect("www.tanee-electric.com",80)) { // REPLACE WITH YOUR SERVER ADDRESS
//    Serial.println(F("Connect Server"));
//    client.println("POST /hotel/add_mega.php HTTP/1.1");
//    //client.println("GET /hotel/add_mega.php HTTP/1.1"); 
//    client.println("Host:www.tanee-electric.com"); // SERVER ADDRESS HERE TOO
//    client.println("Content-Type: application/x-www-form-urlencoded"); 
//    client.print("Content-Length: "); 
//    client.println(data.length()); 
//    client.println(); 
//    client.print(data);
//    Serial.println(F("send data: true")); //Print to serial print for POST to database status is TRUE
  if (client.connect("49.231.30.115",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    Serial.println("Connect Server");
    client.println("POST /hydro/add_tanee.php HTTP/1.1"); 
    client.println("Host:49.231.30.115"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.print("send data: true");
  } 
  if (client.connected()) { 
    client.stop();  //close port connect to server
    Serial.println(F("Disconnect"));
  }
  delay(1000);  //Delay wait for POST to database LOOP
}

//Funtion get volt from sensor
  int getvolt(){
  read_VAC();
  float V = map(adc_vpp,0,AMPLITUDE,0,REAL_VAC*100.00)/100.00;
  //String data;  //My comment
  //data = "Volt = "+String(V,1)+(" VAC"); //My comment
  return V;
}
//Funtion get data from GRAPH VAC
void read_VAC(){
  int cnt;
  //Min and Max value from graph VAC
  adc_max = 0;
  adc_min = 1024;
  for(cnt=0;cnt<SAMPLING;cnt++)
  {
    int adc = analogRead(ADC_PIN);
    if(adc > adc_max){
      adc_max = adc;
    }
    if(adc < adc_min){
      adc_min = adc;
    }
  }
  adc_vpp = adc_max-adc_min;   
}
