#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WebServer server(80);

const char* ssid = "ESP32_TRIP";
const char* password = "12345678";

String destKM = "0.00";
String nextMeter = "0";
String direction = "STRAIGHT";

void drawArrow(String dir) {

  // Arrow position bottom area
  int y = 50;

  if (dir == "LEFT") {
    display.fillTriangle(20,y, 40,y-10, 40,y+10, WHITE);
    display.fillRect(40,y-3, 40,6, WHITE);
  }

  else if (dir == "RIGHT") {
    display.fillTriangle(108,y, 88,y-10, 88,y+10, WHITE);
    display.fillRect(48,y-3, 40,6, WHITE);
  }

  else if (dir == "STRAIGHT") {
    display.fillRect(60,30,8,25,WHITE);
    display.fillTriangle(64,20,50,35,78,35,WHITE);
  }

  else if (dir == "UTURN") {
    display.drawCircle(64,45,15,WHITE);
    display.fillTriangle(49,45, 60,35, 60,55, WHITE);
  }
}

void updateOLED() {

  display.clearDisplay();
  display.setTextColor(WHITE);

  // Destination Line
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("DEST: ");
  display.print(destKM);
  display.print(" KM");

  // Turn Text
  display.setTextSize(2);
  display.setCursor(0,18);
  display.print(nextMeter);
  display.print("m ");
  display.print(direction);

  drawArrow(direction);

  display.display();
}

void handleRoot() {

String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
body { font-family: Arial; text-align:center; }
input,select,button { padding:10px; margin:5px; width:85%; font-size:18px; }
</style>
</head>
<body>

<h2>ESP32 Trip Control</h2>

<input type="text" id="destkm" placeholder="Destination KM (max 25)">
<input type="text" id="meter" placeholder="Next Turn Meter (ex: 120)">
<select id="direction">
<option value="LEFT">LEFT</option>
<option value="RIGHT">RIGHT</option>
<option value="STRAIGHT">STRAIGHT</option>
<option value="UTURN">UTURN</option>
</select>

<button onclick="sendData()">Send</button>

<script>
function sendData(){
let km = document.getElementById("destkm").value;
let meter = document.getElementById("meter").value;
let dir = document.getElementById("direction").value;
fetch("/update?km="+km+"&meter="+meter+"&dir="+dir);
}
</script>

</body>
</html>
)rawliteral";

server.send(200, "text/html", page);
}

void handleUpdate() {

if (server.hasArg("km") && server.hasArg("meter") && server.hasArg("dir")) {

  destKM = server.arg("km");
  nextMeter = server.arg("meter");
  direction = server.arg("dir");

  if (destKM.toFloat() > 25.0) {
    destKM = "25.00";
  }

  if (destKM.toFloat() <= 0.05) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10,25);
    display.print("ARRIVED");
    display.display();
  } else {
    updateOLED();
  }
}

server.send(200, "text/plain", "OK");
}

void setup() {

Serial.begin(115200);

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0,25);
display.print("Starting...");
display.display();

WiFi.softAP(ssid, password);

display.clearDisplay();
display.setCursor(0,25);
display.print("WiFi Ready");
display.display();

server.on("/", handleRoot);
server.on("/update", handleUpdate);
server.begin();
}

void loop() {
server.handleClient();
}
