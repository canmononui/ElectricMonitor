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
  
  char* connector = "rest";
  char* server = "www.tanee-electric.com";
  char* method = "POST";
  String resource = "/hotel/add_tanee.php?";
void setup() {

	/*char* connector = "rest";
	char* server = "www.tanee-electric.com";
	char* method = "GET";
	String resource = "/hotel/add_tanee.php?";*/

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
  resource += "&volt1=230&amp_all1=2.00&amp_air1=2.00&amp_water1=2.00&amp_light1=2.00&amp_plug1=2.00";
  doRequest(connector, server, resource, method);
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

void doRequest(char* conn, char* server, String command, char* method){
	CiaoData data = Ciao.write(conn, server, command, method);
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
