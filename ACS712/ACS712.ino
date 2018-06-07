#include <Wire.h>
int Offset = 519; //
  int   AD[20],VD[20],Step=0;
  float Amp[20],Volt[20],PPower,DPower,PAmp,DAmp,PVolt,DVolt;
  char i,Key; 

//-------------------------------------------

void setup(void)
{   
    Serial.begin(9600);
    Serial.println("START");
    //Serial.print(temp);   
    
              
}
//-----------------------------------------------------
void loop(void)
{ 
    for(i=0;i<20;i++)
    {AD[i] = analogRead(1);delayMicroseconds(10);
     VD[i] = analogRead(0);delayMicroseconds(900);
    }
    
    PVolt = 0;PAmp = 0;PPower = 0;
    for(i=0;i<20;i++)
    {Amp[i] = Calc_Amp(AD[i]);    
     Amp[i] = Amp[i] * Amp[i];
     PAmp   = PAmp + Amp[i];
     
     Volt[i]   = Calc_Volt(VD[i]);  
     Volt[i] = Volt[i] * Volt[i];
     PVolt   = PVolt + Volt[i];
     
    } 
    
    PVolt  = sqrt(PVolt/20);
    PAmp   = sqrt(PAmp/20);
        
    if(PAmp <= 0.05){PAmp = 0;}     
    DAmp = DAmp + PAmp ;    
    PAmp = 0;
    
    if(PVolt <= 10){PVolt = 0;}
    DVolt = DVolt + PVolt ;    
    PVolt = 0;

    /*Serial.print("Volt ");
    Serial.println(DVolt);
    Serial.print("Amp ");
    Serial.println(DAmp);*/
    
    Step++;
    if(Step > 20){DVolt = DVolt/20; DAmp = DAmp/20; 
                  DPower = DVolt * DAmp;                    
                  //lcd.setCursor(12,0);lcd.print(DAmp,2);
                  //lcd.setCursor(3,0);lcd.print(DVolt,0);
                  //lcd.setCursor(12,1);
                  //ShowNum(DPower,4);
                  Serial.print("Volt ");
                  Serial.println(DVolt);
                  Serial.print("Amp ");
                  Serial.println(DAmp);
                  
                  
                  Step = 0;DVolt = 0;DAmp = 0;
                 }
  //Serial.println(Step);               
}
//-----------------------------------------------------
float  Calc_Amp(int AD)
{float A;
   if(AD <= Offset){A = Offset-AD;  
                    A = (A * 22.00)/505.0;
                    A = 0 - A;
                   }
              else{A = AD - Offset;
                   A = (A * 22.00)/505.0;                  
                   }
 
   return(A);
}
//-----------------------------------------------------
float  Calc_Volt(int AD)
{float V;
   if(AD <= 512){   V = 512-AD;
                    V = (V * 1150.00)/512.0;
                    V = 0 - V;                  
                   }
               else{V = AD - 512;
                    V = (V * 1150.00)/512.0;
                   }
  return(V);
}

void NumToChar(unsigned long Num, char  *Buffer,unsigned char Digit)
{char i;
   for(i=(Digit-1);i>= 0;i--)
    { Buffer[i] =  (Num % 10) + '0';  // 234 , 23 , 2
      Num = Num / 10;
    }  
   for(i=0;i<(Digit-1);i++)
    { if(Buffer[i] == '0'){Buffer[i] =  ' ';}else{i =100;}
                         
    }   
}
/*-------------------------------------------------------------*
*  Show Number On LCD                                           *
*-------------------------------------------------------------*/
/*void ShowNum(unsigned long Num,unsigned char Count)
{ char Buf[10],i;
  NumToChar(Num,Buf,Count);  
  for(i=0;i<Count;i++){lcd.print(Buf[i]);}
  
}*/


