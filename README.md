This is demo of BME280 temperature, humidity and pressure sensor connected via I2C with ESP32C3 from Seeed Studio.
Sensor will print data directly to terminal.

Builded using ESP-IDF v5.4.1 and drivers for I2C and sensor from Espressif community.

To add dependency run in main directory: 
- idf.py add-dependency "espressif/bme280: =*"
- idf.py add-dependency "espressif/i2c_bus: =*"

After adding all dependencies connect your ESP to PC and prompt in terminal:
idf.py -p (your port) build flash monitor
