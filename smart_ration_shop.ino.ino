// Smart Ration Shop IoT Project
// ESP8266 + OLED + Keypad + Google Sheets
// Note: Replace Wi-Fi credentials and Script URL before running
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#ifdef CLOSED
#undef CLOSED        // Remove Keypad's CLOSED macro to avoid clash with WiFi
#endif

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// ---------- WIFI ----------
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_NAME";

// ---------- GOOGLE SHEETS ----------
// Deploy Apps Script as web app → copy the URL here
const char* googleScriptURL = "YOUR_GOOGLE_SCRIPT_URL";

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- STOCK ----------
int rice  = 26;
int wheat = 10;
int sugar = 5;

// ---------- KEYPAD (4x3) ----------
const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {3, D7, D6, D5};   // Reversed pin order
byte colPins[COLS] = {1, D4, D3};        // Reversed pin order

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- DISPLAY FUNCTION ----------
void displayStock() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("=== Grocery Stock ===");
  display.println();

  display.print("1. Rice  : ");
  display.println(rice);

  display.print("2. Wheat : ");
  display.println(wheat);

  display.print("3. Sugar : ");
  display.println(sugar);

  display.println();
  display.println("Press 1/2/3 to sell");

  display.display();
}

void displayMessage(const char* msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

// ---------- SEND TO GOOGLE SHEETS ----------
void sendToGoogleSheets() {
  if (WiFi.status() != WL_CONNECTED) {
    displayMessage("WiFi disconnected!");
    delay(1000);
    return;
  }

  displayMessage("Updating sheet...");

  WiFiClientSecure client;
  client.setInsecure();  // Skip SSL cert check (fine for Google)

  HTTPClient http;
  http.begin(client, googleScriptURL);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);  // Google redirects
  http.addHeader("Content-Type", "application/json");

  // Build JSON payload
  String payload = "{\"rice\":" + String(rice) +
                   ",\"wheat\":" + String(wheat) +
                   ",\"sugar\":" + String(sugar) + "}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    displayMessage("Sheet updated!");
  } else {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.print("Error: ");
    display.println(httpCode);
    display.display();
  }

  http.end();
  delay(800);
}

// ---------- SETUP ----------
void setup() {
  Wire.begin(D2, D1);  // SDA=D2, SCL=D1

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  // Connect to WiFi
  displayMessage("Connecting WiFi...");
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    displayMessage("WiFi Connected!");
  } else {
    displayMessage("WiFi FAILED!");
  }
  delay(1000);

  displayStock();
}

// ---------- LOOP ----------
void loop() {
  char key = keypad.getKey();

  if (key) {
    bool changed = false;

    if (key == '1' && rice > 0) {
      rice--;
      changed = true;
    }
    else if (key == '2' && wheat > 0) {
      wheat--;
      changed = true;
    }
    else if (key == '3' && sugar > 0) {
      sugar--;
      changed = true;
    }

    if (changed) {
      sendToGoogleSheets();  // Update sheet only when stock changes
    }

    displayStock();
  }
}