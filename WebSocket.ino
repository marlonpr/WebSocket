#include <WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "IZZI-0BE0";
const char* password = "sbcwinup";
 
char path[] = "/connectVending";
char host[] = "192.168.1.13";
 
WebSocketClient webSocketClient;
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  delay(5000);
 
  if (client.connect(host, 5555)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }
 
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
 
}
 
void loop() {
  String data;
 
  if (client.connected()) {
 
    webSocketClient.sendData(GetMacAddress());
 
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
 
  } else {
    Serial.println("Client disconnected.");
  }
 
  delay(3000);
 
}

String GetMacAddress() {
  return splitString(WiFi.macAddress(), ':');
}

String splitString(String str, char separator) {
  // Split string by separator and join into a string
  String result = "";
  for (int i = 0; i < str.length(); i++) {
    if (str.charAt(i) != separator) {
      result += str.charAt(i);
    }
  }
  return result;
}
