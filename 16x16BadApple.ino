#include <SPIFFS.h>
#include <SPI.h>
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES   4
#define CS_PIN        5

MD_MAX72XX matrix(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
File videoFile;

void setup() {
  Serial.begin(115200);
  // Mount filesystem
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS mount failed");
    while (1);
  }
  // Open raw video
  videoFile = SPIFFS.open("/badapple16.raw", FILE_READ);
  if (!videoFile) {
    Serial.println("Failed to open raw video");
    while (1);
  }
  // Init LED matrix
  matrix.begin();
  matrix.control(MD_MAX72XX::INTENSITY, 3);
  matrix.clear();
}

void loop() {
  uint8_t frame[256];
  // Rewind at end
  if (videoFile.available() < sizeof(frame)) {
    videoFile.seek(0);
  }
  // Read one frame
  videoFile.read(frame, sizeof(frame));

  // Draw 16×16 frame
  for (int y = 0; y < 16; y++) {
    uint16_t bits = 0;
    for (int x = 0; x < 16; x++) {
      bits = (bits << 1) | (frame[y * 16 + x] > 128);
    }
    // Split into two bytes
    uint8_t hi = bits >> 8;
    uint8_t lo = bits & 0xFF;
    int base = (y < 8) ? 0 : 2;
    matrix.setRow(base,     y % 8, hi);
    matrix.setRow(base + 1, y % 8, lo);
  }

  // ~12 FPS
  delay(1000 / 12);
}
