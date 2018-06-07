/*
File: RestClient.ino
This example makes an HTTP request after 10 seconds and shows the result both in
serial monitor and in the wifi console of the Arduino Uno WiFi.

Note: works only with Arduino Uno WiFi Developer Edition.

http://www.arduino.org/learning/tutorials/boards-tutorials/restserver-and-restclient
*/

#include <Wire.h>
#include <UnoWiFiDevEd.h>

  /*int volt;
  float amp_all;
  float amp_air;
  float amp_water;
  float amp_light;
  float amp_plug;*/
  String link="";
  String sensor="";
  char* connector = "rest";
  char* server = "www.tanee-electric.com";
  char* method = "POST";
  String resource = "/hotel/add_tanee.php?V=";
void setup() {
  Serial.begin(9600);
  Ciao.begin();
}

void loop() {
  int volt=227;
  float amp_all=1.11;
  float amp_air=2.22;
  float amp_water=3.33;
  float amp_light=4.44;
  float amp_plug=5.55;
  
  //sensor = "V="+String(volt)+"&A1="+String(amp_all)+"&A2="+String(amp_air)+"&A3="+String(amp_water)+"&A4="+String(amp_light)+"&A5="+String(amp_plug);
  //link = resource+"V=230&A1=1.11&A2=2.22&A3=3.33&A4=4.44&A5=5.55";
  link = resource + String(volt) + "&A1=" + String(amp_all) + "&A2=" + String(amp_air) + "&A3=" + String(amp_water) + "&A4=" + String(amp_light) + "&A5=" + String(amp_plug);
  //link = resource+sensor;
  Serial.println(link);
  CiaoData data = Ciao.write("rest", "www.tanee-electric.com", link); //works
  Serial.println("Send Data");
  delay(2000);
}
/*String makePacket(String url){
  url += "V=";
  url += String(volt);
  url += "&A1=";
  url += String(amp_all);
  url += "&A2=";
  url += String(amp_air);
  url += "&A3=";
  url += String(amp_water);
  url += "&A4=";
  url += String(amp_light);
  url += "&A5=";
  url += String(amp_plug);
  return url;
}
//void doRequest(char* conn, String server, String command){
void doRequest(char* conn, char* server, String command){
  CiaoData data = Ciao.write(conn, server, command);
  if (!data.isEmpty()){
    Ciao.println( "State: " + String (data.get(1)) );
    Ciao.println( "Response: " + String (data.get(2)) );
    Serial.println( "State: " + String (data.get(1)) );
    Serial.println( "Response: " + String (data.get(2)) );
  }
  else{
    Ciao.println ("Write Error");
    Serial.println ("Write Error");
  }
}*/
