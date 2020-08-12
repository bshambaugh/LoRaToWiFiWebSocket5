#include <WebSockets.h>
//#include <WebSocketsServer.h>
//#include <SocketIOclient.h>
#include <WebSocketsClient.h>
#include "heltec.h" 
#include "images.h"
#include <WiFi.h>
// #include <WebSocketClient.h>

// WiFi and WebSocket Stuff

const char* ssid = "NETGEAR09";
const char* password = "silentsky936";

char path[] = "/";
//char host[] = "10.0.0.8";
//int port = 80;
char host[] = "10.0.0.5";
int port = 3000;

WiFiClient client;
WebSocketsClient webSocket;

// LoRa stuff

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void setupWiFi(const char* ssid,const char* password) { 
  
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi.connected");
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
  
}

void setupWebSocket(char host[], char port, char path[]) {
  // add some code in here to check if the wifi is setup
  if(WiFi.status() == WL_CONNECTED) {
    webSocket.begin(host,port,path);
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
  } else {
    Serial.println("WiFiConnection Failed");
  }
}


void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
  Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for(uint32_t i = 0; i < len; i++) {
    if(i % cols == 0) {
      Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    Serial.printf("%02X ", *src);
    src++;
  }
  Serial.printf("\n");
}


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected to Marko");
    }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
        case WStype_PING:
            // pong will be send automatically
            Serial.printf("[WSc] get ping\n");
            break;
        case WStype_PONG:
            // answer to a ping we send
            Serial.printf("[WSc] get pong\n");
            break;
    }

}

void logo(){
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 15 , "Received "+ packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0 , 26 , 128, packet);
  Heltec.display->drawString(0, 0, rssi);  
  Heltec.display->display();
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  LoRaData();
}

void LoraAndOLEDdisplaySetup() {
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
// not sure if I put it here
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setPreambleLength(8);
  LoRa.disableCrc();
  LoRa.setSyncWord(0x12);
 // end of config from forum (https://github.com/HelTecAutomation/ASR650x-Arduino/issues/28)
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  delay(1000);
  //LoRa.onReceive(cbk);
  LoRa.receive();
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  LoraAndOLEDdisplaySetup();
  setupWiFi(ssid,password);
  setupWebSocket(host,port,path);
}

void loop() {
  // put your main code here, to run repeatedly:
  // apparently this code has to be in here for there to be traffic on the network
  webSocket.loop();
  // LoRa stuff
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize);  }
  // end of the LoRa Stuff
  webSocket.sendTXT("hello" + packet);
  delay(1000);

}
