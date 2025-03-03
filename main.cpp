#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_ADDR 0x27  // Проверь адрес сканером!
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
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    printf("Initializing LCD...\n");

    sleep_ms(50);   // Задержка перед инициализацией
    lcd_write_cmd(0x33); // Reset
    sleep_ms(5);
    lcd_write_cmd(0x32); // 4-bit mode
    sleep_ms(5);
    lcd_write_cmd(0x28); // 2 строки, 5x8 точки
    lcd_write_cmd(0x0C); // Включить дисплей, отключить курсор
    lcd_write_cmd(0x06); // Автоинкремент курсора
    lcd_write_cmd(0x01); // Очистка экрана
    sleep_ms(5);

    printf("LCD Initialized!\n");

    while (1) {
        printf("Looping...\n");
        sleep_ms(1000);
    }
}
