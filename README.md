#SKIH3113 — SENSOR-BASED SYSTEMS
<br>SEMESTER A232
<br>Final Assignment: Intelligent Environmental Monitoring System
<br>TITLE: SMART ENVIRONMENTAL MONITORING AND CONTROL SYSTEM.
<br>YOUTUBE LINK: [https://youtu.be/-m3cR2cEtrs]

## Project Description
This project aims to design and implement an Intelligent Environmental Monitoring System using the ESP8266 microcontroller. The system collects data from multiple sensors, processes it, stores it in a database, and controls a relay switch based on predefined environmental conditions. The system also includes a web-based interface for real-time monitoring and data visualization.

## Components
- **Hardware**:
  - ESP8266 microcontroller
  - DHT11 sensor
  - HC-SR04 ultrasonic sensor
  - BH1750 light sensor
  - Relay module
  - Breadboard and jumper wires

- **Software**:
  - Arduino IDE
  - XAMPP (or any LAMP/WAMP stack)
  - Web browser
  - Internet connection

## Setup Instructions

### Step 1: Hardware Assembly
1. **Connect the DHT11 sensor** to the ESP8266:
   - Data pin to D7
   - VCC to 3.3V
   - GND to GND

2. **Connect the HC-SR04 sensor** to the ESP8266:
   - TRIG pin to D5
   - ECHO pin to D6
   - VCC to 5V
   - GND to GND

3. **Connect the BH1750 sensor** to the ESP8266:
   - SDA to D4
   - SCL to D3
   - VCC to 3.3V
   - GND to GND

4. **Connect the Relay module** to the ESP8266:
   - Control pin to D8
   - VCC to 5V
   - GND to GND

### Step 2: Software Configuration
#### 2.1 Uploading the Code to ESP8266
1. Open Final_Assignment.ino in the Arduino IDE.
2. Set your WiFi credentials in the code:
   const char* ssid = "your_SSID";
   const char* password = "your_PASSWORD";
   const char* serverName = "http://your_server_IP/assignment3/store_data.php";
3. Select the board and port:
   Go to Tools > Board and select NodeMCU 1.0 (ESP-12E Module).
   Go to Tools > Port and select the appropriate COM port.
   Upload the code to the ESP8266:
4. Click the Upload button.

#### 2.2 Setting up the Server
1. Copy the project files (fetch_data.php, store_data.php, index.html, styles.css) to the htdocs directory of your XAMPP installation.
2. Import the SQL database:
   -Open phpMyAdmin (usually at http://localhost/phpmyadmin).
   -Create a new database named assignment3.
   -Import assignment3.sql into the assignment3 database.

### Step 3: Running the System
1. Start the server: Ensure Apache and MySQL are running in XAMPP.
2. Open the web interface: Navigate to http://localhost/index.html in your web browser.
3. Monitor the data: The web interface will display real-time and historical sensor data, and control the relay based on environmental conditions.
