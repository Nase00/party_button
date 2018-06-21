#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#define NEO_PIXEL_PIN 15
#define SPEAKER_PIN 13
#define PIXEL_COUNT 7
#define BUTTON_PIN 2

Adafruit_NeoPixel jewel = Adafruit_NeoPixel(PIXEL_COUNT, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
const char* ssid     = "hunter2";
const char* password = "hunter2";
const char* host = "192.168.1.155";

String SONG_VETO = String("[{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerNext\", \"deviceId\": \"eaf15736daea2d8c550795950c984067b6a3df12\"}]\r\n");
String PARTY_SEQUENCE = String("[") +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerPause\", \"deviceIds\": [\"eaf15736daea2d8c550795950c984067b6a3df12\"]}," +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerShuffle\", \"state\": false, \"deviceIds\": [\"eaf15736daea2d8c550795950c984067b6a3df12\"]}," +
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"cylon\"}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"turnOff\", \"id\": 2}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"turnOff\", \"id\": 3}," +
      "{\"type\": \"EMIT_SEND_UNIFIED_COMMAND\", \"name\": \"triggerCommand\", \"commandName\": \"command5\", \"id\": \"Sean.CustomRun\", \"delay\": 100 }," + // Switch to stereo receiver output
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 6000}," +
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"deskLower\", \"additionalHeaders\": { \"timeout\": 250 }, \"delay\": 4000}," +
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"deskPreset\",\"additionalHeaders\": { \"timeout\": 10000 },\"delay\": 6000}," +
    "{\"type\": \"EMIT_TRIGGER_PHOTON_FUNCTION\", \"key\": \"lamprey\", \"delay\": 16000}," +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"transferPlayback\", \"deviceIds\": [\"355beabb5645106941fcdff91fb48e2ad827050e\"], \"delay\": 5750}," +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerPlay\", \"contextUri\": \"spotify:user:nasezero:playlist:4KSxM9RXXLrDJxgb9zxAlo\", \"deviceId\": \"eaf15736daea2d8c550795950c984067b6a3df12\", \"delay\": 6000}," +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerVolume\", \"volumePercent\": 100, \"delay\": 5750}," +
    "{\"type\": \"EMIT_SEND_UNIFIED_COMMAND\", \"name\": \"triggerCommand\", \"value\": 6, \"delay\": 40000}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"turnOn\", \"id\": 3, \"delay\": 15500}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"turnOff\", \"id\": 2, \"delay\": 15500}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"brightness\", \"arg\": 75, \"id\": 3, \"delay\": 15750}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"colorLoop\", \"id\": 3, \"delay\": 16000}," +

    // Flash with beginning of song (halloween)
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 21000}," +
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 24000}," +
    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 28000}," +

    // Flash with beginning of song (beta)
//    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 6500}," +
//    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 7500}," +
//    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 8500}," +
//    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 9500}," +
//    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 10500}," +
//    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"flashPurple\", \"delay\": 11500}," +

    // Soften effects long-term
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"effect\", \"arg\": \"none\", \"id\": 3, \"delay\": 115000}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"hue\", \"arg\": 65535, \"id\": 3, \"delay\": 115050}," +
    "{\"type\": \"EMIT_SEND_HUE_COMMAND\", \"func\": \"brightness\", \"arg\": 70, \"id\": 3, \"delay\": 115000}," +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerVolume\", \"volumePercent\": 90, \"delay\": 115000}," +
    "{\"type\": \"EMIT_SEND_SPOTIFY_COMMAND\", \"name\": \"playerVolume\", \"volumePercent\": 80, \"delay\": 125000}," +

    "{\"type\": \"EMIT_FORWARD_HTTP_REQUEST\", \"key\": \"rain\"}" +
    "]\r\n";

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

int brightness = 0;
bool rising = true;
int buttonState = 0;
bool wasPressed = false;

int numTones = 10;
int tones[] = {440, 440, 440, 440, 415, 392, 370, 349, 330, 311, 294, 277, 261};

void pulse(bool wasPressed) {
  jewel.setPixelColor(0, 0, 0, 255);

  if (brightness >= 255) {
    rising = false;
  }

  if (brightness <= 0) {
    rising = true;
  }

  if (rising) {
    brightness++;
  } else {
    brightness--;
  }

  Serial.print(wasPressed);

  if (wasPressed) {
    for (int x = 1; x < PIXEL_COUNT; x++) {
      jewel.setPixelColor(x, 0, 0, brightness);
    }
  } else {
    for (int x = 1; x < PIXEL_COUNT; x++) {
      jewel.setPixelColor(x, brightness, brightness, brightness);
    }  
  }

  jewel.show();
  delay(10);
}

void playTones() {
  for (int i = 0; i < numTones; i++) {
    tone(SPEAKER_PIN, tones[i]);
    delay(250);
  }
  noTone(SPEAKER_PIN);
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return jewel.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return jewel.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  WheelPos -= 170;
  return jewel.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  jewel.begin();
  jewel.show();
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendCommands(const String data) {
  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 4000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/api";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Content-Type: application/json\r\n" +
    "event: BATCH_EVENTS_FROM_WEBHOOK\r\n" +
    "id: hunter2\r\n" +
    "webhookbody: " + data + "\n");

  delay(500);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}


void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  pulse(wasPressed);

  if (buttonState == LOW && !wasPressed) {
    playTones();
    sendCommands(PARTY_SEQUENCE);

    wasPressed = true;
  } else if (buttonState == LOW && wasPressed) {
    sendCommands(SONG_VETO);
  }
}

