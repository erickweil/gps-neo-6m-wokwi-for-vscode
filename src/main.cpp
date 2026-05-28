#include <Arduino.h>
#include <TinyGPS++.h>

// --- PIN GPS NEO-6M (Interface UART2) ---
const int PIN_GPS_RX     = 16;   // Hubungkan ke TX pada modul GPS
const int PIN_GPS_TX     = 17;   // Hubungkan ke RX pada modul GPS

TinyGPSPlus gps;
HardwareSerial GPSSerial(2);

unsigned long lastGpsPrintMs = 0;

void setup() {
  Serial.begin(115200);
  
  // Menggunakan Serial2 untuk berkomunikasi dengan modul GPS custom
  GPSSerial.begin(9600, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);

  Serial.println("=====================================");
  Serial.println("Sistem Uji Coba GPS NEO-6M (Wokwi)");
  Serial.println("=====================================");
}
void loop() {
  while (GPSSerial.available()) {
    char c = GPSSerial.read();
    // Serial.write(c);
    gps.encode(c);
  }

  if (millis() - lastGpsPrintMs > 1000) {
    lastGpsPrintMs = millis();

    if (gps.location.isValid()) {
      Serial.print("Latitude: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" | Longitude: ");
      Serial.println(gps.location.lng(), 6);
    } else {
      Serial.println("GPS terbaca, tapi data belum valid / checksum salah");
    }
  }
}