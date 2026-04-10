#include "lcd.hpp"
#include <stdio.h>

#define LCD_CLEAR_DISPLAY          0x01
#define LCD_RETURN_HOME            0x02
#define LCD_ENTRY_MODE_SET         0x06
#define LCD_DISPLAY_CONTROL        0x0C
#define LCD_FUNCTION_SET           0x28 // 4-bit mode, 2 lines, 5x8 dots
#define LCD_BACKLIGHT              0x08
#define LCD_EN                     0x04 // Enable bit
#define LCD_RS                     0x01 // Register Select bit

LCD::LCD(I2C_HandleTypeDef* h, uint8_t address){
	this ->hi2c = h;
	this ->addr = address;
}

void LCD::WriteByte(uint8_t byte, uint8_t rs_bit) {
    uint8_t data_u = (byte & 0xf0);
    uint8_t data_l = ((byte << 4) & 0xf0);
    uint8_t data_t[4];

    data_t[0] = data_u | rs_bit | LCD_BACKLIGHT | LCD_EN;
    data_t[1] = data_u | rs_bit | LCD_BACKLIGHT;
    data_t[2] = data_l | rs_bit | LCD_BACKLIGHT | LCD_EN;
    data_t[3] = data_l | rs_bit | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(hi2c, addr, data_t, 4, 100);
}

void LCD::Init() {
    HAL_Delay(50);  // чекаємо поки дисплей стартує

    // Reset послідовність — ОБОВ'ЯЗКОВО тричі 0x30 в верхньому нібблі
    // Але в 4-бітному режимі надсилаємо тільки верхній нібл!
    uint8_t init_seq[4];

    // Крок 1: надсилаємо 0x3 (верхній нібл) — перший раз
    init_seq[0] = 0x30 | LCD_BACKLIGHT | LCD_EN;
    init_seq[1] = 0x30 | LCD_BACKLIGHT;
    HAL_I2C_Master_Transmit(hi2c, addr, init_seq, 2, 100);
    HAL_Delay(5);

    // Крок 2: другий раз
    HAL_I2C_Master_Transmit(hi2c, addr, init_seq, 2, 100);
    HAL_Delay(1);

    // Крок 3: третій раз
    HAL_I2C_Master_Transmit(hi2c, addr, init_seq, 2, 100);
    HAL_Delay(1);

    // Крок 4: переходимо на 4-бітний режим (надсилаємо 0x2)
    init_seq[0] = 0x20 | LCD_BACKLIGHT | LCD_EN;
    init_seq[1] = 0x20 | LCD_BACKLIGHT;
    HAL_I2C_Master_Transmit(hi2c, addr, init_seq, 2, 100);
    HAL_Delay(1);

    // Далі вже повні команди через WriteByte (обидва нібли):
    WriteByte(LCD_FUNCTION_SET, 0);   // 4-bit, 2 lines, 5x8
    HAL_Delay(1);
    WriteByte(LCD_DISPLAY_CONTROL, 0); // display on, cursor off
    HAL_Delay(1);
    WriteByte(LCD_CLEAR_DISPLAY, 0);
    HAL_Delay(5);                      // clear потребує більше часу!
    WriteByte(LCD_ENTRY_MODE_SET, 0);
    HAL_Delay(1);
}

void LCD::Print(char data) {
    WriteByte((uint8_t)data, LCD_RS);
}

void LCD::Print(const char* pData) {
    while (*pData) {
        WriteByte(*pData++, LCD_RS);
    }
}

void LCD::Print(uint32_t data) {
    char buf[12];
    sprintf(buf, "%lu", data);
    Print(buf);
}

void LCD::SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    WriteByte(address, 0);
}

void LCD::Clear() {
    WriteByte(LCD_CLEAR_DISPLAY, 0);
    HAL_Delay(2);
}
