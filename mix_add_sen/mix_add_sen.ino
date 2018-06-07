#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include "EmonLib.h"
EnergyMonitor emon1;  // Create an instance1
EnergyMonitor emon2;  // Create an instance2
EnergyMonitor emon3;  // Create an instance3
EnergyMonitor emon4;  // Create an instance4
EnergyMonitor emon5;  // Create an instance5
//VOLT
#define SAMPLING 300
#define VOFFSET  512 
#define ADC_PIN A0
#define AMPLITUDE 411.00
#define REAL_VAC  227.5
int adc_max,adc_min;
int adc_vpp;
String link="";
char* connector = "rest";
char* server = "www.tanee-electric.com";
String resource = "/hotel/wifi_add.php?V=";
int count=0;
void setup() {
  Serial.begin(9600);
  Ciao.begin();
  EnergyMonitor emon1;  // Create an instance1
  EnergyMonitor emon2;  // Create an instance2
  EnergyMonitor emon3;  // Create an instance3
  EnergyMonitor emon4;  // Create an instance4
  EnergyMonitor emon5;  // Create an instance5
}

void loop() {

  int volt = getvolt();
  float amp_all    = emon1.calcIrms(1480); //Call funtion calculator Irms 
  float amp_air    = emon2.calcIrms(1480); //Call funtion calculator Irms
  float amp_water  = emon3.calcIrms(1480); //Call funtion calculator Irms
  float amp_light  = emon4.calcIrms(1480); //Call funtion calculator Irms
  float amp_plug   = emon5.calcIrms(1480); //Call funtion calculator Irms
  /*if(amp_all<=0.39){
    amp_all=0.00;
    }*/ 
  //Gen value
  link = resource + String(volt) + "&A1=" + String(amp_all)+ "&A2=" + String(amp_air)+ "&A3=" + String(amp_water)+ "&A4=" + String(amp_light)+ "&A5=" + String(amp_plug);
  Serial.println(link);
  CiaoData data = Ciao.write("rest", "www.tanee-electric.com", link);
  Serial.println(F("Send Data"));
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
  delay(1000);
}

int getvolt(){
  read_VAC();
  float V = map(adc_vpp,0,AMPLITUDE,0,REAL_VAC*100.00)/100.00;
  String data;
  data = "Volt = "+String(V,1)+(" VAC"); 
  return V;
}
void read_VAC(){
  int cnt;
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
