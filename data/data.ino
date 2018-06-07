//A0 Amp_all
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
String data="";
int Offset=519,Step=0;
int VD[20],AD1[20],AD2[20],AD3[20],AD4[20],AD5[20];
float volt,amp_all,amp_air,amp_water,amp_light,amp_plug;
float Volt[20],PVolt,DVolt;
float Amp1[20],Amp2[20],Amp3[20],Amp4[20],Amp5[20];
float PAmp1,PAmp2,PAmp3,PAmp4,PAmp5;
float DAmp1,DAmp2,DAmp3,DAmp4,DAmp5;
char i,Key;
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      }
}

void loop() {
//loop for get data from sensor
  for(i=0;i<20;i++){
     VD[i] = analogRead(0);delayMicroseconds(500);
     AD1[i] = analogRead(1);delayMicroseconds(500);
     AD2[i] = analogRead(2);delayMicroseconds(500);
     AD3[i] = analogRead(3);delayMicroseconds(500);
     AD4[i] = analogRead(4);delayMicroseconds(500);
     AD5[i] = analogRead(5);delayMicroseconds(500);
    }
    
  PVolt = 0;  PAmp1 = 0;PAmp2 = 0;PAmp3 = 0;PAmp4 = 0;PAmp5 = 0;
  for(i=0;i<20;i++){
//1  Amp1[i] = Calc_Amp(AD1[i]);    
     Amp1[i] = Amp1[i] * Amp1[i];
     PAmp1   = PAmp1 + Amp1[i];
//2  Amp2[i] = Calc_Amp(AD2[i]);   
     Amp2[i] = Amp2[i] * Amp2[i];
     PAmp2   = PAmp2 + Amp2[i];
//3  Amp3[i] = Calc_Amp(AD3[i]);    
     Amp3[i] = Amp3[i] * Amp3[i];
     PAmp3   = PAmp3 + Amp3[i]; 
//4  Amp4[i] = Calc_Amp(AD4[i]);    
     Amp4[i] = Amp4[i] * Amp4[i];
     PAmp4   = PAmp4 + Amp4[i];
//5  Amp5[i] = Calc_Amp(AD5[i]);    
     Amp5[i] = Amp5[i] * Amp5[i];
     PAmp5   = PAmp5 + Amp5[i];
//V  Volt[i]   = Calc_Volt(VD[i]);  
     Volt[i] = Volt[i] * Volt[i];
     PVolt   = PVolt + Volt[i];  
    }
    PVolt  = sqrt(PVolt/20);
    PAmp1   = sqrt(PAmp1/20);
    PAmp2   = sqrt(PAmp2/20);
    PAmp3   = sqrt(PAmp3/20);
    PAmp4   = sqrt(PAmp4/20);
    PAmp5   = sqrt(PAmp5/20);
     
//1 if(PAmp1 <= 0.05){PAmp1 = 0;}     
    DAmp1 = DAmp1 + PAmp1;    
    PAmp1 = 0;
//2 if(PAmp2 <= 0.05){PAmp2 = 0;}     
    DAmp2 = DAmp2 + PAmp2;    
    PAmp2 = 0;
//3 if(PAmp3 <= 0.05){PAmp3 = 0;}     
    DAmp3 = DAmp3 + PAmp3;    
    PAmp3 = 0;
//4 if(PAmp4 <= 0.05){PAmp4 = 0;}     
    DAmp4 = DAmp4 + PAmp4;    
    PAmp4 = 0;
//5 if(PAmp5 <= 0.05){PAmp5 = 0;}     
    DAmp5 = DAmp4 + PAmp5;    
    PAmp5 = 0;
//V if(PVolt <= 10){PVolt = 0;}
    DVolt = DVolt + PVolt ;    
    PVolt = 0;
    Step++;
    
    if(Step > 20){
       volt = DVolt/20; 
       amp_all = DAmp1/20;
       amp_air = DAmp2/20;
       amp_water = DAmp3/20;
       amp_light = DAmp4/20;
       amp_plug = DAmp5/20;                     
       Step = 0;DVolt = 0;DAmp1 = 0,DAmp2 = 0,DAmp3 = 0,DAmp4 = 0,DAmp5 = 0;
  
  volt = 2; 
  amp_all = 2;
  amp_air = 2;
  amp_water = 2;
  amp_light = 2;
  amp_plug = 2;
  Serial.println(volt);
  Serial.println(amp_all);
  Serial.println(amp_air);
  Serial.println(amp_water);
  Serial.println(amp_light);
  Serial.println(amp_plug);
  
  data = "&volt1=" + String(volt) + "&amp_all1=" + String(amp_all) + "&amp_air1=" + String(amp_air) + "&amp_water1=" + String(amp_water) + "&amp_light1=" + String(amp_light) + "&amp_plug1=" + String(amp_plug);
  Serial.println(data);
  if (client.connect("www.tanee-electric.com",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    Serial.println("Connect Server");
    client.println("POST /hotel/add_tanee.php HTTP/1.1"); 
    client.println("Host:www.tanee-electric.com"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.print("send data: true");
  } 
  if (client.connected()) { 
    client.stop();
    Serial.println("Disconnect");
  }
delay(1000);
//}
       
} //end loop

float Calc_Amp(int AD){
  float A;
  if(AD <= Offset){
    A = Offset-AD;  
    A = (A * 22.00)/505.0;
    A = 0 - A;
    }
  else{
    A = AD - Offset;
    A = (A * 22.00)/505.0;                  
    }
  return(A);
}
float Calc_Volt(int AD){
  float V;
  if(AD <= 512){   
    V = 512-AD;
    V = (V * 1150.00)/512.0;
    V = 0 - V;                  
    }
  else{
    V = AD - 512;
    V = (V * 1150.00)/512.0;
    }
  return(V);
}






