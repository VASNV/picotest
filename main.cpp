#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define LED_PIN 25  // Встроенный светодиод
#define I2C_PORT i2c0
#define SDA_PIN 0
#define SCL_PIN 1
#define LCD_ADDR 0x3F // Проверь адрес дисплея (может быть 0x3F)

// Функция отправки команды дисплею
void lcd_send_command(uint8_t cmd) {
    uint8_t buf[1] = {cmd};
    i2c_write_blocking(I2C_PORT, LCD_ADDR, buf, 1, false);
}

// Включение подсветки (если поддерживается)
void lcd_backlight_on() {
    lcd_send_command(0x08); // Некоторые дисплеи включают подсветку этим
}

int main() {
    stdio_init_all();

    // Инициализация светодиода
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Инициализация I2C
    i2c_init(I2C_PORT, 100000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Включение подсветки
    lcd_backlight_on();

    // Мигание светодиодом
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
}
