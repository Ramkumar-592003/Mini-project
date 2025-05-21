 #include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN D2         
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "ESPtest";
const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  // Seed random number with analog noise
  randomSeed(analogRead(A0));
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    int soil = analogRead(A0);

    // Simulated NPK values
    int nitrogen = random(150, 300);     // Example range
    int phosphorus = random(100, 200);
    int potassium = random(120, 250);

    String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    html += "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>body{font-family:sans-serif;background:#f4f4f4;text-align:center;padding:20px;}h1{color:#2c3e50;}div.card{background:white;padding:20px;margin:20px auto;max-width:300px;border-radius:10px;box-shadow:0 0 10px rgba(0,0,0,0.1);}span{font-size:24px;}</style>";
    html += "<title>Smart Garden</title></head><body>";
    html += "<h1>🌿 Smart Garden Dashboard 🌿</h1>";
    html += "<div class='card'><p>🌡️ Temperature: <span>" + String(temp) + " °C</span></p></div>";
    html += "<div class='card'><p>💧 Humidity: <span>" + String(hum) + " %</span></p></div>";
    html += "<div class='card'><p>🌱 Soil Moisture: <span>" + String(soil) + "%</span></p></div>";
    html += "<div class='card'><p>🧪 Nitrogen (N): <span>" + String(nitrogen) + " ppm</span></p></div>";
    html += "<div class='card'><p>🧪 Phosphorus (P): <span>" + String(phosphorus) + " ppm</span></p></div>";
    html += "<div class='card'><p>🧪 Potassium (K): <span>" + String(potassium) + " ppm</span></p></div>";
    html += "</body></html>";

    client.print(html);
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}




