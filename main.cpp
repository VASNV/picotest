#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_ADDR 0x27
#define I2C_PORT i2c0
#define SDA_PIN 0
#define SCL_PIN 1

void lcd_write_cmd(uint8_t cmd) {
    uint8_t buf[1] = {cmd};
    i2c_write_blocking(I2C_PORT, I2C_ADDR, buf, 1, false);
}

int main() {
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    // Очистка дисплея
    lcd_write_cmd(0x01);
    sleep_ms(5);

    while (1) {
        printf("Hello, Pico!\n");
        sleep_ms(1000);
    }

    return 0;
}
