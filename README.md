# 🚦 ESP32 Ultrasonic Traffic Light System

A smart traffic light control system using ESP32, HC-SR04 ultrasonic sensor, and RGB LEDs. The system automatically controls traffic lights based on distance measurements from the ultrasonic sensor.

## 📋 Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Wiring Diagram](#wiring-diagram)
- [Software Setup](#software-setup)
- [How It Works](#how-it-works)
- [Distance Ranges](#distance-ranges)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)

## ✨ Features

- **Real-time Distance Measurement**: Uses HC-SR04 ultrasonic sensor for accurate distance detection
- **Automatic Traffic Light Control**: LEDs respond automatically based on measured distances
- **Serial Monitor Output**: Clear distance readings and light status messages
- **Configurable Distance Ranges**: Easy to modify distance thresholds for different use cases
- **Low Latency**: 500ms update interval for responsive control

## 🛠 Hardware Requirements

| Component                 | Quantity | Description                     |
| ------------------------- | -------- | ------------------------------- |
| ESP32 Development Board   | 1        | Main microcontroller            |
| HC-SR04 Ultrasonic Sensor | 1        | Distance measurement sensor     |
| Red LED                   | 1        | Traffic light indicator         |
| Yellow LED                | 1        | Traffic light indicator         |
| Green LED                 | 1        | Traffic light indicator         |
| Resistors (220Ω)          | 3        | Current limiting for LEDs       |
| Breadboard                | 1        | For prototyping connections     |
| Jumper Wires              | Multiple | Male-to-male and male-to-female |

## 🔌 Wiring Diagram

### HC-SR04 Ultrasonic Sensor

```
HC-SR04    →    ESP32
VCC        →    5V (or 3.3V)
GND        →    GND
TRIG       →    GPIO 22
ECHO       →    GPIO 19
```

### Traffic Light LEDs

```
LED Color    →    ESP32 Pin    →    Resistor    →    GND
Red LED      →    GPIO 4       →    220Ω        →    GND
Yellow LED   →    GPIO 16      →    220Ω        →    GND
Green LED    →    GPIO 17      →    220Ω        →    GND
```

### Complete Wiring Schematic

```
                    ESP32
                 ┌─────────┐
    HC-SR04      │         │      LEDs
   ┌─────────┐   │         │   ┌──────────┐
   │   VCC   ├───┤ 5V      │   │   RED    ├───┤ GPIO 4
   │   GND   ├───┤ GND     │   │ YELLOW   ├───┤ GPIO 16
   │  TRIG   ├───┤ GPIO 22 │   │  GREEN   ├───┤ GPIO 17
   │  ECHO   ├───┤ GPIO 19 │   └──────────┘
   └─────────┘   │         │
                 └─────────┘
```

## 💻 Software Setup

### Prerequisites

- [PlatformIO IDE](https://platformio.org/platformio-ide) or [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 board support package

### Installation Steps

1. **Clone or Download the Project**

   ```bash
   git clone https://github.com/dannycahyo/rgb-sonic.git
   cd rgb-sonic
   ```

2. **Open in PlatformIO**

   - Open PlatformIO IDE
   - File → Open Project
   - Select the project folder

3. **Build and Upload**

   ```bash
   platformio run --target upload
   ```

4. **Monitor Serial Output**
   ```bash
   platformio device monitor --baud 115200
   ```

## ⚙️ How It Works

The system operates in a continuous loop:

1. **Distance Measurement**: The HC-SR04 sensor sends an ultrasonic pulse and measures the echo return time
2. **Distance Calculation**: The time is converted to distance using the speed of sound (343 m/s)
3. **Traffic Light Control**: Based on the measured distance, the appropriate LED is activated
4. **Serial Output**: Distance and light status are logged to the serial monitor

### Code Flow

```
Setup → Initialize Pins → Main Loop:
├── Read Distance from Sensor
├── Calculate Distance in cm
├── Control Traffic Lights
├── Log to Serial Monitor
└── Wait 500ms → Repeat
```

## 📏 Distance Ranges

| Distance Range | LED Color     | Status        | Description                         |
| -------------- | ------------- | ------------- | ----------------------------------- |
| 0 - 20 cm      | 🔴 **RED**    | TOO CLOSE!    | Danger zone - object too near       |
| 21 - 50 cm     | 🟡 **YELLOW** | CAUTION       | Medium distance - proceed with care |
| 51 - 200 cm    | 🟢 **GREEN**  | SAFE DISTANCE | Safe zone - all clear               |
| > 200 cm       | ⚫ **OFF**    | OUT OF RANGE  | No object detected                  |

## 🚀 Usage

1. **Power On**: Connect ESP32 to power source (USB or external)
2. **Monitor Output**: Open serial monitor at **115200 baud rate**
3. **Test the System**: Move objects in front of the sensor
4. **Observe**: Watch LEDs change based on distance and monitor serial output

### Expected Serial Output

```
===========================================
  HC-SR04 Ultrasonic Sensor + Traffic Light
              ESP32 Control
===========================================
TRIG Pin: 22
ECHO Pin: 19
RED Pin: 4
YELLOW Pin: 16
GREEN Pin: 17
===========================================
Distance Ranges:
  0-20 cm   : RED (Too Close!)
  21-50 cm  : YELLOW (Caution)
  51-200 cm : GREEN (Safe Distance)
  >200 cm   : No Light (Out of Range)
===========================================

Distance: 15.2 cm [RED LIGHT - TOO CLOSE!]
Distance: 35.7 cm [YELLOW LIGHT - CAUTION]
Distance: 85.3 cm [GREEN LIGHT - SAFE DISTANCE]
Distance: 250.1 cm [OUT OF RANGE - NO LIGHTS]
```

## 🔧 Troubleshooting

### Common Issues

#### 1. Garbled Serial Output

- **Problem**: Serial monitor shows unreadable characters
- **Solution**: Set baud rate to **115200** in serial monitor

#### 2. LEDs Not Working

- **Problem**: LEDs don't light up or behave incorrectly
- **Solutions**:
  - Check wiring connections
  - Verify resistor values (220Ω recommended)
  - Test LEDs with multimeter
  - Check GPIO pin assignments in code

#### 3. Inaccurate Distance Readings

- **Problem**: Sensor readings are inconsistent or wrong
- **Solutions**:
  - Ensure HC-SR04 has stable power (5V recommended)
  - Check TRIG and ECHO pin connections
  - Avoid obstacles near the sensor
  - Ensure sensor is mounted securely

#### 4. No Serial Output

- **Problem**: No output in serial monitor
- **Solutions**:
  - Check USB cable connection
  - Verify correct COM port selection
  - Ensure ESP32 is properly flashed
  - Try different USB cable

### Pin Configuration Issues

If you need to change pins, modify these definitions in `main.cpp`:

```cpp
#define TRIG_PIN 22     // Ultrasonic sensor trigger pin
#define ECHO_PIN 19     // Ultrasonic sensor echo pin
#define RED_PIN 4       // Red LED pin
#define YELLOW_PIN 16   // Yellow LED pin
#define GREEN_PIN 17    // Green LED pin
```

## 🔄 Customization

### Adjusting Distance Ranges

Modify the `controlTrafficLight()` function in `src/main.cpp`:

```cpp
if (distance > 0 && distance <= 20) {        // RED range
if (distance > 20 && distance <= 50) {       // YELLOW range
if (distance > 50 && distance <= 200) {      // GREEN range
```

### Changing Update Frequency

Modify the delay in the main loop:

```cpp
delay(500);  // Change to desired milliseconds
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 🙏 Acknowledgments

- ESP32 community for excellent documentation
- PlatformIO team for the great development environment
- Arduino community for the foundational libraries

## 📞 Support

If you encounter any issues or have questions:

- Open an issue on GitHub
- Check the troubleshooting section above
- Review PlatformIO and ESP32 documentation

---

**Happy Coding! 🚀**
