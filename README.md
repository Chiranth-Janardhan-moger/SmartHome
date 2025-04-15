# SmartHome
A complete smart home automation system built using ESP32 and a Python Flask web dashboard. This project allows you to monitor real-time environmental data, including temperature, humidity, and harmful gases.

## 📁 Project Structure

- `Main.ino`: Arduino sketch that controls sensors and modules (e.g., DHT, WiFi).
- `app.py`: Python Flask app for the web dashboard.
- `templates/`: HTML files for the frontend.

## 🔌 Required Arduino Libraries

Make sure to install these libraries in your Arduino IDE:

- `WiFi.h` (for ESP32 or ESP8266 Wi-Fi support)
- `DHT.h` (for DHT11/DHT22 sensor support)
- `Adafruit Unified Sensor`
- `ArduinoJson` (optional, if using JSON communication)
  
## 🛠️ Setup Instructions

1. **Arduino**
   - Connect your ESP32 board.
   - Upload `Main.ino` after installing required libraries.

2. **Python Flask App**
   - Install Flask: `pip install flask`
   - Run the app:
     ```bash
     python app.py
     ```
   - Open `http://localhost:5000` in your browser.

## 🌐 Web Dashboard Features

- Realtime monitoring of temperature, humidity, and Harmful Gases.

## 🧑‍💻 Author

Chiranth

---

**Happy hacking!** 🔧🌡️📶
