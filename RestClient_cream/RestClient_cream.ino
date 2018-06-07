/*
File: RestClient.ino
This example makes an HTTP request after 10 seconds and shows the result both in
serial monitor and in the wifi console of the Arduino Uno WiFi.

Note: works only with Arduino Uno WiFi Developer Edition.

http://www.arduino.org/learning/tutorials/boards-tutorials/restserver-and-restclient
*/

#include <Wire.h>
#include <UnoWiFiDevEd.h>
  int volt;
  float amp_all;
  float amp_air;
  float amp_water;
  float amp_light;
  float amp_plug;
  const char* connector = "rest";
  const char* server = "www.tanee-electric.com";
  const char* method = "POST";
  const char* resource = "/hotel/add_tanee.php?";

void setup() {
  /*const char* connector = "rest";
  const char* server = "www.tanee-electric.com";
  const char* method = "POST";
  const char* resource = "/hotel/add_tanee.php?";*/
	Serial.begin(9600);
	Ciao.begin();	
}

void loop() {
  volt=230;
  amp_all=1.00;
  amp_air=1.00;
  amp_water=1.00;
  amp_light=1.00;
  amp_plug=1.00;
  doRequest(connector, server, makePacket(resource),method);
  delay(1000);
}

String makePacket(String url){
  url += "volt1=";
  url += String(volt);
  url += "&amp_all1=";
  url += String(amp_all);
  url += "&amp_air1=";
  url += String(amp_air);
  url += "&amp_water1=";
  url += String(amp_water);
  url += "&amp_light1=";
  url += String(amp_light);
  url += "&amp_plug1=";
  url += String(amp_plug);
  return url;
}
void doRequest(const char* conn, const char* server, String command, const char* method){
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
}
