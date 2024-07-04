#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

// WiFi credentials
const char* ssid = "A15"; // WiFi SSID
const char* password = "chong1151"; // WiFi password
const char* serverName = "http://192.168.69.8/assignment3/store_data.php"; // Server URL to store data

// Define DHT11 sensor pin and type
#define DHTPIN D7 // DHT11 sensor pin
#define DHTTYPE DHT11 // DHT11 sensor type

// Define HC-SR04 sensor pins
#define TRIGPIN D5 // HC-SR04 trigger pin
#define ECHOPIN D6 // HC-SR04 echo pin

// Define Relay switch pin
#define RELAYPIN D8 // Relay pin

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize BH1750 sensor
BH1750 lightMeter;

// Arrays to store readings for data processing
float temperatureReadings[6];
float humidityReadings[6];
long distanceReadings[6];
float lightReadings[6];
int readIndex = 0; // Index for storing readings in arrays
int numReadings = 0; // To keep track of the number of readings

// Flag to indicate WiFi connection status
bool wifiConnected = false;

// Function to measure distance using HC-SR04
long measureDistance() {
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    long duration = pulseIn(ECHOPIN, HIGH);
    long distance = duration * 0.034 / 2;
    return distance;
}

// Function to calculate average of an array
template <typename T>
T calculateAverage(T* readings, int numReadings) {
    T sum = 0;
    for (int i = 0; i < numReadings; i++) {
        sum += readings[i];
    }
    return sum / numReadings;
}

// Function to calculate minimum of an array
template <typename T>
T calculateMin(T* readings, int numReadings) {
    T min = readings[0];
    for (int i = 1; i < numReadings; i++) {
        if (readings[i] < min) {
            min = readings[i];
        }
    }
    return min;
}

// Function to calculate maximum of an array
template <typename T>
T calculateMax(T* readings, int numReadings) {
    T max = readings[0];
    for (int i = 1; i < numReadings; i++) {
        if (readings[i] > max) {
            max = readings[i];
        }
    }
    return max;
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize DHT sensor
    dht.begin();

    // Initialize I2C for BH1750 sensor using GPIO 2 (D4) for SDA and GPIO 0 (D3) for SCL
    Wire.begin(D4, D3);
    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
        Serial.println(F("BH1750 initialized successfully"));
    } else {
        Serial.println(F("Error initializing BH1750"));
    }

    // Initialize HC-SR04 sensor pins
    pinMode(TRIGPIN, OUTPUT);
    pinMode(ECHOPIN, INPUT);

    // Initialize Relay switch pin
    pinMode(RELAYPIN, OUTPUT);
    digitalWrite(RELAYPIN, LOW); // Ensure relay is off at start

    // Connect to WiFi
    connectToWiFi();
}

void loop() {
    // Reconnect to WiFi if disconnected and not in safe mode
    if (!wifiConnected) {
        connectToWiFi();
    }

    // Read DHT11 sensor data
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        temperatureReadings[readIndex] = temperature;
        humidityReadings[readIndex] = humidity;

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" *C");
    }

    // Read HC-SR04 sensor data
    long distance = measureDistance();
    distanceReadings[readIndex] = distance;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Read BH1750 sensor data
    float lux = lightMeter.readLightLevel();
    lightReadings[readIndex] = lux;
    if (lux < 0) {
        Serial.println("Failed to read from BH1750 sensor!");
    } else {
        Serial.print("Light: ");
        Serial.print(lux);
        Serial.println(" lx");
    }

    // Increment readIndex and wrap around if necessary
    readIndex = (readIndex + 1) % 6;
    if (numReadings < 6) {
        numReadings++;
    }

    // Calculate averages, min, and max only if we have enough readings
    if (numReadings == 6) {
        float avgTemperature = calculateAverage(temperatureReadings, 6);
        float avgHumidity = calculateAverage(humidityReadings, 6);
        long avgDistance = calculateAverage(distanceReadings, 6);
        float avgLight = calculateAverage(lightReadings, 6);

        float minTemperature = calculateMin(temperatureReadings, 6);
        float minHumidity = calculateMin(humidityReadings, 6);
        long minDistance = calculateMin(distanceReadings, 6);
        float minLight = calculateMin(lightReadings, 6);

        float maxTemperature = calculateMax(temperatureReadings, 6);
        float maxHumidity = calculateMax(humidityReadings, 6);
        long maxDistance = calculateMax(distanceReadings, 6);
        float maxLight = calculateMax(lightReadings, 6);

        // Print calculated values to serial monitor
        Serial.print("Average Temperature: ");
        Serial.print(avgTemperature);
        Serial.println(" *C");

        Serial.print("Average Humidity: ");
        Serial.print(avgHumidity);
        Serial.println(" %");

        Serial.print("Average Distance: ");
        Serial.print(avgDistance);
        Serial.println(" cm");

        Serial.print("Average Light: ");
        Serial.print(avgLight);
        Serial.println(" lx");

        Serial.print("Min Temperature: ");
        Serial.print(minTemperature);
        Serial.println(" *C");

        Serial.print("Min Humidity: ");
        Serial.print(minHumidity);
        Serial.println(" %");

        Serial.print("Min Distance: ");
        Serial.print(minDistance);
        Serial.println(" cm");

        Serial.print("Min Light: ");
        Serial.print(minLight);
        Serial.println(" lx");

        Serial.print("Max Temperature: ");
        Serial.print(maxTemperature);
        Serial.println(" *C");

        Serial.print("Max Humidity: ");
        Serial.print(maxHumidity);
        Serial.println(" %");

        Serial.print("Max Distance: ");
        Serial.print(maxDistance);
        Serial.println(" cm");

        Serial.print("Max Light: ");
        Serial.print(maxLight);
        Serial.println(" lx");

        // Control Relay switch based on average temperature
        bool relayStatus = false;
        if (avgTemperature > 25) {
            digitalWrite(RELAYPIN, HIGH); // Turn relay on
            Serial.println("Relay ON");
            relayStatus = true;
        } else {
            digitalWrite(RELAYPIN, LOW); // Turn relay off
            Serial.println("Relay OFF");
            relayStatus = false;
        }

        // Send data to the server if WiFi is connected
        if (wifiConnected) {
            WiFiClient client;
            HTTPClient http;

            http.setTimeout(2000);  // Set timeout to 2000 milliseconds (2 seconds)
            http.begin(client, serverName);
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");

            // Prepare data for HTTP POST request
            String httpRequestData = "avgTemperature=" + String(avgTemperature) + "&avgHumidity=" + String(avgHumidity) + "&avgDistance=" + String(avgDistance) + "&avgLight=" + String(avgLight) +
                                      "&minTemperature=" + String(minTemperature) + "&minHumidity=" + String(minHumidity) + "&minDistance=" + String(minDistance) + "&minLight=" + String(minLight) +
                                      "&maxTemperature=" + String(maxTemperature) + "&maxHumidity=" + String(maxHumidity) + "&maxDistance=" + String(maxDistance) + "&maxLight=" + String(maxLight) +
                                      "&relay=" + String(relayStatus ? "ON" : "OFF");
            int httpResponseCode = http.POST(httpRequestData);

            // Check the HTTP response code and print the server response
            if (httpResponseCode > 0) {
                String response = http.getString();
                Serial.println(httpResponseCode);
                Serial.println(response);
            } else {
                Serial.print("Error on sending POST: ");
                Serial.println(http.errorToString(httpResponseCode));
            }

            http.end();
        } else {
            Serial.println("WiFi not connected. Data not sent to server.");
        }
    }

    // Wait for 30 seconds before next loop
    delay(30000);
}

// Function to connect to WiFi with retry mechanism
void connectToWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    int maxRetries = 3; // Maximum number of retries for WiFi connection
    int retryCount = 0;
    
    // Attempt to connect to WiFi with retries
    while (WiFi.status() != WL_CONNECTED && retryCount < maxRetries) {
        delay(10000);
        Serial.print(".");
        retryCount++;
    }

    // Check if connected to WiFi
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to WiFi");
        wifiConnected = true;
    } else {
        Serial.println("Failed to connect to WiFi. Entering safe mode.");
        wifiConnected = false;
    }
}
