#include <Wire.h>
#include <SPI.h>
int Offset = 519;
int Step=0;
int VD[20];
float volt;
float Volt[20],PVolt,DVolt;
void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i=0;i<20;i++){
    VD[i] = analogRead(0);delayMicroseconds(500);
    Volt[i]   = Calc_Volt(VD[i]);  
    Volt[i] = Volt[i] * Volt[i];
    PVolt   = PVolt + Volt[i];
    }
    
  PVolt  = sqrt(PVolt/20);
  
  if(PVolt <= 10){PVolt = 0;}
    DVolt = DVolt + PVolt ;    
    PVolt = 0;
    Step++;

if(Step > 20){
  volt = DVolt/20;
  Step = 0;DVolt = 0; 
  Serial.println(volt);
  delay(1000);
  }
}

float Calc_Volt(int AD){
  float V;
     if(AD <= 512){   
        V = 512-AD;
        V = (V * 1150.00)/512.0;
        V = 0 - V;                  
      }
      else{V = AD - 512;
        V = (V * 1150.00)/512.0;               }
        return(V);
}
