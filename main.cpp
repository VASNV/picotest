#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define LED_PIN 25      // Встроенный светодиод
#define I2C_PORT i2c0
#define SDA_PIN 0
#define SCL_PIN 1
#define LCD_ADDR 0x3F   // Адрес дисплея (проверь сканером!)
#define LCD_COLS 16     // Количество столбцов на дисплее
#define LCD_ROWS 2      // Количество строк

// Функция отправки команды дисплею
void lcd_send_command(uint8_t cmd) {
    uint8_t buf[1] = {cmd};
    i2c_write_blocking(I2C_PORT, LCD_ADDR, buf, 1, false);
}

// Функция отправки данных (текста) на дисплей
void lcd_send_data(uint8_t data) {
    uint8_t buf[1] = {data | 0x40}; // RS = 1
    i2c_write_blocking(I2C_PORT, LCD_ADDR, buf, 1, false);
}

// Очистка экрана
void lcd_clear() {
    lcd_send_command(0x01);
    sleep_ms(2);
}

// Установка курсора
void lcd_set_cursor(int col, int row) {
    int row_offsets[] = {0x00, 0x40}; 
    lcd_send_command(0x80 | (col + row_offsets[row]));
}

// Включение подсветки (некоторые дисплеи поддерживают)
void lcd_backlight_on() {
    lcd_send_command(0x08);
}

// Инициализация дисплея
void lcd_init() {
    sleep_ms(50);
    lcd_send_command(0x33); // Reset
    lcd_send_command(0x32); // 4-bit mode
    lcd_send_command(0x28); // 2 строки, 5x8 точки
    lcd_send_command(0x0C); // Включить дисплей, отключить курсор
    lcd_send_command(0x06); // Автоинкремент курсора
    lcd_clear();
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

    // Инициализация дисплея
    lcd_init();
    lcd_backlight_on();

    // Анимация бегущего квадрата
    char box = 0xFF; // Символ залитого квадрата (если поддерживается)
    
    while (true) {
        // Мигание светодиодом
        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);

        // Анимация квадрата
        for (int i = 0; i < LCD_COLS; i++) {
            lcd_clear();
            lcd_set_cursor(i, 0);
            lcd_send_data(box);
            sleep_ms(100);
        }
    }
}
