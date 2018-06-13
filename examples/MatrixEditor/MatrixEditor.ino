#include <ESP8266WiFi.h>            
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "static.h"

const char *ssid = "YourSSIDHere";
const char *password = "YourPSKHere";

ESP8266WebServer server(80);    //Webserver Object

void rootHandler() {       //Define the handling function for root path (HTML message)
	server.send(200, "text/html", INDEX);
}

void jsHandler() { 				//Define the handling function for the javascript path
	server.send(200, "text/html", "javascriptCode");
}

void cssHandler() {
	server.send(200, "text/html", "cssCode");
}

void handleNotFound() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ) {
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}
	server.send ( 404, "text/plain", message );
}

void setup() {

	Serial.begin(115200);                                             //Open Serial connection
	WiFi.mode ( WIFI_STA );
	WiFi.begin(ssid, password);                          //Connect to the WiFi network

	while (WiFi.status() != WL_CONNECTED) {    //Wait for connection
		delay(500);
		Serial.println("Waiting to connect…");
	}

	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());  //Print the local IP

	server.on("/", HTTP_GET, rootHandler);
	server.on("/javascript", HTTP_GET, jsHandler);
	server.on("/css", HTTP_GET, cssHandler);

	server.onNotFound ( handleNotFound );
	server.begin(); //Start the server

	Serial.println("Server listening");

}

void loop() {
	server.handleClient(); //Handling of incoming requests
}