#include <WebSockets.h>
//#include <WebSocketsServer.h>
//#include <SocketIOclient.h>
#include <WebSocketsClient.h>

#include <WiFi.h>
// #include <WebSocketClient.h>

const char* ssid = "NETGEAR09";
const char* password = "silentsky936";

char path[] = "/";
char host[] = "10.0.0.8";
int port = 80;

WiFiClient client;
WebSocketsClient webSocket;

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupWiFi(ssid,password);
  // delay(5000);
  // WStype_CONNECTED
  /*
  if (WStype_DISCONNECTED) {
     Serial.println("connected!");
  } else {
    Serial.println("not connected");
  } 
  */
 ///  webSocket.begin(host,port,path);
 // set this to point to another server on an ESP32
 //  webSocket.begin("10.0.0.5",3000,"/");
 ///  webSocket.onEvent(webSocketEvent);
 ///  webSocket.setReconnectInterval(5000);
    setupWebSocket(host,port,path);
 //  webSocket.enableHeartbeat(15000, 3000, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  // apparently this code has to be in here for there to be traffic on the network
  webSocket.loop();
   webSocket.sendTXT("hello");
   delay(1000);

}
