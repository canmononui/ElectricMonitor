#define BUFFER 700

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if(Serial.available())
  {
    String req = Serial.readStringUntil('\n');
    if(req.indexOf(F("start")) != -1)
    {
      unsigned char flag=0;
      while(1)
      {
        int x = analogRead(A0);
        
        if(x>512)
        {
          flag=1;
        }
        if((x<=512)&&(flag==1))
        {
          break;
        }
      }
      for(int i=0;i<BUFFER;i++)
      {
        int data = analogRead(A0);
        Serial.write(data>>8);
        Serial.write(data&0xFF);
      }
      Serial.print("end");
    }	
  }
}
