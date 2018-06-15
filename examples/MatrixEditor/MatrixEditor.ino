/*
  upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <FS.h>
#include <Neo.h>

#include "credentials.h"

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

Neo disp(4, D4);

byte frame[32];

void rootHandler() {
  server.sendHeader("Location", "/index.html",true);   //Redirect to our html web page
  server.send(302, "text/plane","");
}

void renderHandler() {
  if ( !server.hasArg("frame") || server.arg("frame") == NULL) {
    server.send(400, "text/plain", "400: Invalid Request");
    return;
  }
  server.send(200, "text/html", server.arg("frame"));
  // Logging received data
  const char *p = server.arg("frame").c_str();
  while (*p != 0)  { Serial.print(*p, HEX); p++; }

  //TODO: decode frame data and update display
}

void handleWebRequests(){
  if (loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

void webSocketHandler(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      break;
    }
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if (decodeFrame(payload)) {
        Serial.println('Display Updated');
      }
      break;
  }  
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("\r\n");

  setupDisplay();
  startSPIFFS();
  startWIFI();
  startServer();
  startWebSocket();
}

void loop() {
  server.handleClient();
  webSocket.loop();
}

bool loadFromSpiffs(String path){
  String dataType = "text/plain";
  if (path.endsWith("/")) path += "index.htm";
 
  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html")) dataType = "text/html";
  else if (path.endsWith(".htm")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js")) dataType = "application/javascript";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/pdf";
  else if (path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }
 
  dataFile.close();
  return true;
}

void setupDisplay() {
  disp.begin();
  disp.setBrightness(0);
  disp.clearDisplay();  
}

void startSPIFFS() {
  SPIFFS.begin();                             // Start the SPI Flash File System (SPIFFS)
  Serial.println("SPIFFS started. Contents:");
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {                      // List the file system contents
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }
}

void startWIFI() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  IPAddress myIP = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(myIP);
  Serial.println("\r\n");
}

void startServer() {
  server.on("/", HTTP_GET, rootHandler);
  server.on("/render", HTTP_POST, renderHandler);
  server.onNotFound(handleWebRequests);
  server.begin();
  Serial.println("HTTP Server started.");
}

void startWebSocket() {
  webSocket.begin();
  webSocket.onEvent(webSocketHandler);
//  Serial.println("WebSocket server started");
}

// Helpers
String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
}

bool decodeFrame(uint8_t * p) {
  if (p[0] == '#') {
    p++;
    for (uint8_t j = 0; j < 32; j++) {
      char tmp[3];
      for (uint8_t i = 0; i < 3; i++) {
        tmp[i] = (char) *p;
        p++;  
      }
      Serial.println(String(tmp).toInt());
      frame[j] = (byte) String(tmp).toInt();
      disp.renderRow((uint8_t)(j % 4), (uint8_t) (j / 4) + 1, frame[j] );
    }
  return true;
  }
  return false;
}