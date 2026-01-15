#include <U8g2lib.h>
#include <DHT.h>

/* ================= DISPLAY =================
   SSD1306 128x64 SPI OLED
*/
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(
  U8G2_R0,
  /* CS=*/ 10,
  /* DC=*/ 9,
  /* RESET=*/ 8
);

/* ================= SENSORS ================= */
#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ_PIN A0

/* ================= UI OFFSET ================= */
#define X_OFFSET 5   // 👉 shift everything 5 pixels to the right

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  u8g2.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  int air    = analogRead(MQ_PIN);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tf);

    // ---------- TITLE ----------
    u8g2.drawStr(18 + X_OFFSET, 10, "AIR MONITOR");

    // ---------- TEMPERATURE ----------
    u8g2.setCursor(0 + X_OFFSET, 28);
    u8g2.print("Temp: ");
    if (isnan(temp)) {
      u8g2.print("--");
    } else {
      u8g2.print(temp, 1);
      u8g2.print(" C");
    }

    // ---------- HUMIDITY ----------
    u8g2.setCursor(0 + X_OFFSET, 40);
    u8g2.print("Hum : ");
    if (isnan(hum)) {
      u8g2.print("--");
    } else {
      u8g2.print(hum, 0);
      u8g2.print(" %");
    }

    // ---------- AIR QUALITY ----------
    u8g2.setCursor(0 + X_OFFSET, 52);
    u8g2.print("Air : ");
    u8g2.print(air);

    if (air < 300)       u8g2.print(" GOOD");
    else if (air < 600)  u8g2.print(" MOD");
    else                 u8g2.print(" BAD");

  } while (u8g2.nextPage());

  delay(2000);
}