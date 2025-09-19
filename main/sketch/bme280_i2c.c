#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "bme280.h"
#include "i2c_bus.h"

#define I2C_MASTER_SCL_IO 7 // for esp32c3 from seeed studio
#define I2C_MASTER_SDA_IO 6 // adjust if needed
#define I2C_MASTER_FREQ_HZ 100000

static const char *TAG = "BME280";

void app_main(void)
{
    // 1. Create I2C bus using i2c_bus abstraction
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_bus_handle_t i2c_bus = i2c_bus_create(I2C_NUM_0, &conf);
    // 2. Create BME280 handle
    bme280_handle_t bme280 = bme280_create(i2c_bus, 0x76);
    ESP_ERROR_CHECK(bme280_default_init(bme280));

    vTaskDelay(pdMS_TO_TICKS(1000)); // wait for propper init i2c

    ESP_LOGI(TAG, "BME280 initialized successfully");

    // 3. Read sensor periodically
    while (1)
    {
        float temperature = 0.0, humidity = 0.0, pressure = 0.0;

        ESP_ERROR_CHECK(bme280_read_temperature(bme280, &temperature));
        ESP_ERROR_CHECK(bme280_read_humidity(bme280, &humidity));
        ESP_ERROR_CHECK(bme280_read_pressure(bme280, &pressure));

        ESP_LOGI(TAG, "Temperature: %.2f °C", temperature);
        ESP_LOGI(TAG, "Humidity: %.2f %%", humidity);
        ESP_LOGI(TAG, "Pressure: %.2f hPa", pressure / 100.0f);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
