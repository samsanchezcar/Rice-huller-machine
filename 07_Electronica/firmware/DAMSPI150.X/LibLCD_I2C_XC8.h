/*
 * LibLCD_I2C_XC8.h
 * Libreria LCD 20x4 HD44780 via modulo I2C PCF8574
 * Compatible con PIC18F4550 @ 8 MHz — XC8 >= 3.0
 *
 * Proyecto DAMSPI-150 | PAI 2017275 | Grupo B
 * Gabriel E. Bojacá M. + Samuel D. Sánchez C.
 *
 * Conexion:
 *   RC3/SCL → SCL del modulo PCF8574
 *   RC4/SDA ↔ SDA del modulo PCF8574
 *   Pull-up 4.7kΩ a +5V (generalmente incluido en el modulo)
 *   Direccion I2C: 0x27 (A2=A1=A0=VCC) — verificar segun modulo
 */

#ifndef LIB_LCD_I2C_XC8_H
#define LIB_LCD_I2C_XC8_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// Bits del PCF8574 mapeados al LCD HD44780
#define LCD_RS_BIT  0    // P0 → RS
#define LCD_RW_BIT  1    // P1 → RW (siempre 0 = escritura)
#define LCD_EN_BIT  2    // P2 → EN (Enable)
#define LCD_BL_BIT  3    // P3 → Backlight (1=encendido)
#define LCD_D4_BIT  4    // P4 → D4
#define LCD_D5_BIT  5    // P5 → D5
#define LCD_D6_BIT  6    // P6 → D6
#define LCD_D7_BIT  7    // P7 → D7

// Comandos HD44780
#define LCD_CMD_CLEAR       0x01
#define LCD_CMD_HOME        0x02
#define LCD_CMD_ENTRY_MODE  0x06    // Incrementar, sin desplazamiento
#define LCD_CMD_DISPLAY_ON  0x0C    // Display ON, cursor OFF, blink OFF
#define LCD_CMD_FUNC_SET    0x28    // 4-bit, 2 lineas, 5x8 dots
#define LCD_CMD_DDRAM_BASE  0x80

// Direcciones DDRAM para LCD 20x4
static const uint8_t LCD_ROW_ADDR[4] = {0x00, 0x40, 0x14, 0x54};

// Estado del backlight
static uint8_t _lcd_addr    = 0x27;
static uint8_t _lcd_backlight = (1 << LCD_BL_BIT);

// ============================================================
// FUNCIONES I2C (MSSP del PIC18F4550)
// ============================================================

static void i2c_start(void) {
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN);
}

static void i2c_stop(void) {
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN);
}

static void i2c_write(uint8_t data) {
    SSPBUF = data;
    while (SSPSTATbits.BF);
    while (SSPCON2bits.ACKSTAT);
}

// ============================================================
// ENVIO AL PCF8574
// ============================================================
static void lcd_i2c_send_byte(uint8_t data) {
    i2c_start();
    i2c_write((_lcd_addr << 1) | 0);   // Direccion + escritura
    i2c_write(data);
    i2c_stop();
}

static void lcd_pulse_enable(uint8_t data) {
    lcd_i2c_send_byte(data | (1 << LCD_EN_BIT));
    __delay_us(1);
    lcd_i2c_send_byte(data & ~(1 << LCD_EN_BIT));
    __delay_us(50);
}

static void lcd_send_nibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = _lcd_backlight;
    if (rs) data |= (1 << LCD_RS_BIT);
    data |= (nibble & 0xF0);           // Nibble alto en D7:D4
    lcd_pulse_enable(data);
}

static void lcd_send_byte(uint8_t value, uint8_t rs) {
    lcd_send_nibble(value & 0xF0, rs);         // Nibble alto primero
    lcd_send_nibble((value << 4) & 0xF0, rs);  // Nibble bajo
    __delay_us(50);
}

// ============================================================
// API PUBLICA
// ============================================================

void LCD_I2C_Init(uint8_t addr) {
    _lcd_addr = addr;
    __delay_ms(50);

    // Secuencia de inicializacion en modo 4 bits (HD44780 datasheet)
    lcd_send_nibble(0x30, 0); __delay_ms(5);
    lcd_send_nibble(0x30, 0); __delay_us(150);
    lcd_send_nibble(0x30, 0); __delay_us(150);
    lcd_send_nibble(0x20, 0); __delay_us(150);  // Cambiar a 4 bits

    // Configuracion
    lcd_send_byte(LCD_CMD_FUNC_SET,    0);
    lcd_send_byte(LCD_CMD_DISPLAY_ON,  0);
    lcd_send_byte(LCD_CMD_CLEAR,       0); __delay_ms(2);
    lcd_send_byte(LCD_CMD_ENTRY_MODE,  0);
}

void LCD_I2C_Clear(void) {
    lcd_send_byte(LCD_CMD_CLEAR, 0);
    __delay_ms(2);
}

void LCD_I2C_Home(void) {
    lcd_send_byte(LCD_CMD_HOME, 0);
    __delay_ms(2);
}

void LCD_I2C_SetCursor(uint8_t col, uint8_t row) {
    if (row > 3) row = 3;
    if (col > 19) col = 19;
    uint8_t addr = LCD_CMD_DDRAM_BASE | (LCD_ROW_ADDR[row] + col);
    lcd_send_byte(addr, 0);
}

void LCD_I2C_WriteChar(char c) {
    lcd_send_byte((uint8_t)c, 1);
}

void LCD_I2C_Print(const char *str) {
    while (*str) {
        LCD_I2C_WriteChar(*str++);
    }
}

void LCD_I2C_Backlight(bool on) {
    _lcd_backlight = on ? (1 << LCD_BL_BIT) : 0;
    lcd_i2c_send_byte(_lcd_backlight);
}

void LCD_I2C_PrintInt(int16_t val) {
    if (val < 0) { LCD_I2C_WriteChar('-'); val = -val; }
    if (val >= 100) LCD_I2C_WriteChar('0' + val / 100);
    if (val >= 10)  LCD_I2C_WriteChar('0' + (val % 100) / 10);
    LCD_I2C_WriteChar('0' + val % 10);
}

#endif /* LIB_LCD_I2C_XC8_H */
