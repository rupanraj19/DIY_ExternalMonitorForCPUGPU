#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readString(); // Read the incoming message

    // Clear the display
    display.clearDisplay();

    // Set text size for the label
    display.setTextSize(2);  
    display.setCursor(0, 0);  // Start at the top-left corner
    display.println("Hi, Sumo:");

    // Split the message into CPU and GPU usage
    int cpuIndex = message.indexOf("CPU:");
    int gpuIndex = message.indexOf("GPU:");

    String cpuUsage = message.substring(cpuIndex, message.indexOf("%", cpuIndex) + 1);  // Get CPU usage
    String gpuUsage = message.substring(gpuIndex, message.indexOf("%", gpuIndex) + 1);  // Get GPU usage

    // Set text size for the data
    display.setTextSize(2);  // Larger text size for CPU and GPU values
    display.setCursor(0, 30);  // Set cursor below the "Received:" label
    display.println(cpuUsage);  // Display CPU usage

    display.setCursor(0, 50);  // Move to the next line
    display.println(gpuUsage);  // Display GPU usage

    // Display everything on the OLED screen
    display.display();
  }
}
