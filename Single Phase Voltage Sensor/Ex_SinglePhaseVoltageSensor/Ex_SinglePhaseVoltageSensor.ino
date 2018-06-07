#define SAMPLING 300
#define VOFFSET  512 
#define ADC_PIN A0
#define AMPLITUDE 411.00
#define REAL_VAC  233.5
int adc_max,adc_min;
int adc_vpp;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
 
  read_VAC();
  float V = map(adc_vpp,0,AMPLITUDE,0,REAL_VAC*100.00)/100.00;
  String data;
  data = "Volt = "+String(V,1)+(" VAC"); 
  Serial.println(data);
  delay(200);
}

void read_VAC()
{
  int cnt;
  adc_max = 0;
  adc_min = 1024;
  
  for(cnt=0;cnt<SAMPLING;cnt++)
  {
    int adc = analogRead(ADC_PIN);
    if(adc > adc_max)
    {
      adc_max = adc;
    }
    if(adc < adc_min)
    {
      adc_min = adc;
    }
  }
  adc_vpp = adc_max-adc_min;   
}


