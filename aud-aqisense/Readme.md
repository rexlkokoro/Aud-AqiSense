# Air Quality and Environmental Monitoring System

This project is a low-cost, real-time Air Quality and Environmental Monitoring System developed using the Arduino Uno platform. It integrates a DHT11 temperature and humidity sensor, an MQ-series gas sensor, and a 128×64 SPI OLED display (SSD1306).

The system provides live data visualization of atmospheric conditions and categorizes air quality based on gas concentration levels.

---

## Key Features

* **Temperature Sensing:** High-precision digital readings via the DHT11 sensor.
* **Humidity Monitoring:** Real-time relative humidity tracking.
* **Gas Detection:** Air quality monitoring utilizing MQ-series sensors (e.g., MQ-2 or MQ-135).
* **Visual Interface:** Data visualization on an SSD1306 128×64 SPI OLED display.
* **Power Versatility:** Compatible with USB, power banks, or 9V DC adapters.
* **Scalability:** Modular design allowing for easy integration of additional sensors or modules.

---

## Hardware Components

| Component | Description |
| --- | --- |
| **Arduino Uno** | Primary microcontroller unit |
| **DHT11 Sensor** | Digital temperature and humidity sensor |
| **MQ Gas Sensor** | MQ-2 or MQ-135 for air quality/gas detection |
| **SSD1306 OLED** | 128×64 Graphical display (SPI interface) |
| **Breadboard** | For circuit prototyping |
| **Jumper Wires** | Interconnection cables |
| **Power Source** | USB cable or 9V DC adapter |

---

## Circuit Configuration

### OLED Display (SPI Interface)

| OLED Pin | Arduino Pin |
| --- | --- |
| GND | GND |
| VCC | 5V |
| SCL | D13 |
| SDA | D11 |
| CS | D10 |
| DC | D9 |
| RES | D8 |

### Sensor Connections

| Sensor Pin | Arduino Pin |
| --- | --- |
| DHT11 VCC | 5V |
| DHT11 DATA | D2 |
| DHT11 GND | GND |
| MQ VCC | 5V |
| MQ GND | GND |
| MQ Analog Out (A0) | A0 |

---

## Operational Logic

The system processes environmental data through the following workflow:

1. **Data Acquisition:** The DHT11 provides digital environmental data, while the MQ sensor outputs an analog voltage proportional to gas concentrations.
2. **Processing:** The Arduino Uno converts these signals into readable metrics.
3. **Classification:** Air quality is categorized based on the following thresholds:

> * **Value < 300:** Good Quality
> * **Value 300 – 600:** Moderate Quality
> * **Value > 600:** Poor Quality (Bad)
> 
> 

---

## Software Requirements

### Development Environment

* Arduino IDE (Version 1.8.x or higher)

### Required Libraries

The following libraries must be installed via the Arduino Library Manager:

* **U8g2** by Oliver
* **DHT sensor library** by Adafruit
* **Adafruit Unified Sensor**

---

## Implementation Code

```cpp
#include <U8g2lib.h>
#include <DHT.h>

// OLED Display Configuration (SSD1306 SPI)
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(
  U8G2_R0,
  10,  // CS
  9,   // DC
  8    // RESET
);

// Sensor Configuration
#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ_PIN A0
#define X_OFFSET 5  // UI Alignment Margin

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

    u8g2.drawStr(18 + X_OFFSET, 10, "AIR MONITOR");

    // Temperature Display
    u8g2.setCursor(X_OFFSET, 28);
    u8g2.print("Temp: ");
    if (!isnan(temp)) {
      u8g2.print(temp, 1);
      u8g2.print(" C");
    } else u8g2.print("--");

    // Humidity Display
    u8g2.setCursor(X_OFFSET, 40);
    u8g2.print("Hum : ");
    if (!isnan(hum)) {
      u8g2.print(hum, 0);
      u8g2.print(" %");
    } else u8g2.print("--");

    // Air Quality Display
    u8g2.setCursor(X_OFFSET, 52);
    u8g2.print("Air : ");
    u8g2.print(air);

    if (air < 300) u8g2.print(" GOOD");
    else if (air < 600) u8g2.print(" MOD");
    else u8g2.print(" BAD");

  } while (u8g2.nextPage());

  delay(2000);
}

```

---

## Observations and Technical Notes

* **Thermal Stability:** Temperature and humidity readings demonstrate high stability in indoor environments.
* **Sensor Calibration:** The MQ-series sensor requires a warm-up period of approximately 60 seconds to ensure accurate readings.
* **Sensitivity:** The gas sensor exhibits immediate response when exposed to concentrated smoke or combustible gases.

---

## Future Enhancements

* **Audible Alerts:** Integration of a piezo buzzer for threshold-based alarms.
* **Data Visualization:** Implementation of real-time bar graphs on the OLED display.
* **IoT Integration:** Adding Wi-Fi capabilities via ESP8266/ESP32 for remote monitoring.
* **Cloud Logging:** Syncing data with mobile dashboards for historical analysis.

---

## Project Contributors

**Group DR-1**

* Manas Kumar Singh
* Ayush Kumar
* Naman Jha