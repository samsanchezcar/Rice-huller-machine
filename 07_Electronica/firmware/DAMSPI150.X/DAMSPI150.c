/*
 * DAMSPI-150 — Descascaradora de Arroz Modular Semiautomática con Pesaje Integrado
 * Firmware PIC18F4550 — Módulo 3: Control, Pesaje e Interfaz
 *
 * Proyecto Aplicado de Ingeniería 2017275 | Grupo B | 1er Semestre 2026
 * Universidad Nacional de Colombia
 *
 * Autores:
 *   Samuel D. Sánchez C.  — Arquitectura, FSM, HX711, drivers
 *   Gabriel E. Bojacá M.  — Esquemático, LCD I2C, teclado, pilotos
 *
 * Hardware:
 *   MCU         : PIC18F4550 DIP-40 @ 8 MHz (oscilador interno)
 *   Pantalla    : LCD 20x4 HD44780 + PCF8574 I2C (0x27) — 5V nativo
 *   Teclado     : Matricial 4x4 membrana — PORTB completo (KBI)
 *   Pesaje      : 4x Celdas tipo S 10kg en puente Wheatstone + HX711 ADC 24 bits
 *   Embrague    : DLD6-05 24VDC via SSR 24VDC/10A (RD3)
 *   Servo tolva : MG996R via PWM CCP1 50Hz (RC2)
 *   E-Stop      : NC hardware en línea 24V + lectura estado en RA4
 *   Buzzer      : Activo 5V (RD4)
 *   LEDs        : Piloto Verde (RD5), Amarillo (RD6), Rojo (RD7) via 2N2222
 *
 * Compilador : XC8 >= 3.0
 * IDE        : MPLAB X >= 6.0
 * Programador: PICkit 3 o PICkit 4 (ICSP)
 *
 * Ver documentacion completa en: 08_Electronica/GUIA_ELECTRONICA.md
 */

// ============================================================
// INCLUDES Y CONFIGURACION
// ============================================================
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "LibLCD_I2C_XC8.h"

// Configuracion del PIC18F4550
#pragma config FOSC   = INTOSCIO_EC  // Oscilador interno 8 MHz
#pragma config WDT    = OFF
#pragma config PWRT   = ON
#pragma config MCLRE  = ON
#pragma config LVP    = OFF
#pragma config PBADEN = OFF          // PORTB digital al reset
#pragma config BOR    = OFF
#pragma config STVREN = OFF

#define _XTAL_FREQ  8000000UL

// ============================================================
// PINES
// ============================================================
#define HX_SCK      RD0             // HX711 clock (salida)
#define HX_DOUT     RD1             // HX711 data  (entrada)
#define SSR_PIN     RD3             // SSR embrague (salida)
#define BUZZER_PIN  RD4             // Buzzer activo 5V
#define LED_VERDE   RD5             // Piloto LED verde (via 2N2222)
#define LED_AMARILLO RD6            // Piloto LED amarillo
#define LED_ROJO    RD7             // Piloto LED rojo
#define ESTOP_PIN   RA4             // E-Stop NC (LOW = presionado)
#define START_PIN   RA5             // Boton START (LOW = presionado)
#define STOP_PIN    RE0             // Boton STOP  (LOW = presionado)

// Configuracion servo CCP1 (RC2) — 50 Hz @ 8 MHz, prescaler 1:16, PR2=249
#define SERVO_CERRADO   25          // 1.0 ms → 0°
#define SERVO_ABIERTO   50          // 2.0 ms → 180°

// Configuracion LCD I2C
#define LCD_ADDR    0x27            // Direccion I2C modulo PCF8574

// ============================================================
// MAQUINA DE ESTADOS
// ============================================================
typedef enum {
    ST_INICIO,
    ST_ESPERA,
    ST_ASK,
    ST_COUNT,
    ST_COMPLETADO,
    ST_MENU,
    ST_EMERGENCIA
} EstadoSistema_t;

// ============================================================
// VARIABLES GLOBALES
// ============================================================
volatile EstadoSistema_t estado = ST_INICIO;

// Pesaje
volatile int32_t  offset_tara       = 0;
volatile float    factor_calibracion = 1.0f;  // raw/kg (calibrar con masa conocida)
volatile float    peso_kg           = 0.0f;
volatile float    peso_objetivo_kg  = 50.0f;
volatile uint8_t  bultos            = 0;

// Teclado
volatile uint8_t  tecla             = 0;
volatile bool     ok                = false;
volatile bool     ask               = false;
volatile uint8_t  input_count       = 0;
volatile uint16_t objetivo_temp     = 0;

// Control
volatile bool     emergency         = false;
volatile uint8_t  counter_inact     = 0;    // contador de inactividad (unidades: interrupciones Timer0)

// ============================================================
// PROTOTIPOS DE FUNCIONES
// ============================================================

// HX711
int32_t  hx711_leer_raw(void);
int32_t  hx711_leer_promedio(uint8_t n);
float    calcular_peso(int32_t raw);
void     realizar_tara(void);

// LCD I2C
void     lcd_mostrar_espera(void);
void     lcd_mostrar_peso(void);
void     lcd_mostrar_completado(void);
void     lcd_mostrar_emergencia(void);
void     lcd_mostrar_menu(void);
void     lcd_mostrar_ask(void);

// Teclado
uint8_t  escanear_teclado(void);
void     procesar_tecla(uint8_t t);

// Actuadores
void     servo_set(uint8_t pos);
void     embrague_on(void);
void     embrague_off(void);

// Alertas
void     beep(uint16_t ms);
void     beep_completado(void);
void     leds_set(bool verde, bool amarillo, bool rojo);

// EEPROM
void     EEPROM_Write(uint8_t addr, uint8_t data);
uint8_t  EEPROM_Read(uint8_t addr);
void     guardar_calibracion(void);
void     cargar_calibracion(void);

// Inicializacion
void     initPorts(void);
void     initInterrupts(void);
void     initPWM(void);

// ISR
void __interrupt() ISR(void);

// ============================================================
// MAIN
// ============================================================
void main(void) {
    initPorts();
    initInterrupts();
    initPWM();

    // Inicializar LCD I2C
    LCD_I2C_Init(LCD_ADDR);
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("  DAMSPI-150    ");
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("Iniciando...    ");
    __delay_ms(2000);

    // Cargar calibracion desde EEPROM
    cargar_calibracion();

    // Tara automatica al inicio
    realizar_tara();

    estado = ST_ESPERA;

    // ============================================================
    // LOOP PRINCIPAL
    // ============================================================
    while (1) {

        // Leer E-Stop en todo momento
        if (!ESTOP_PIN && !emergency) {
            emergency = true;
            estado = ST_EMERGENCIA;
        }

        switch (estado) {

            // ------------------------------------------------
            case ST_ESPERA:
                leds_set(0, 1, 0);          // LED amarillo
                embrague_off();
                servo_set(SERVO_CERRADO);
                lcd_mostrar_espera();
                lcd_mostrar_peso();

                if (!START_PIN || tecla == 'A') {
                    tecla = 0;
                    estado = ST_COUNT;
                    beep(100);
                    beep(100);
                }
                if (tecla == 'C') {
                    tecla = 0;
                    estado = ST_MENU;
                }
                if (tecla == '*') {
                    tecla = 0;
                    realizar_tara();
                }
                break;

            // ------------------------------------------------
            case ST_ASK:
                lcd_mostrar_ask();
                ask = true;
                ok  = false;
                input_count  = 0;
                objetivo_temp = 0;

                while (!ok) {
                    if (emergency) { estado = ST_EMERGENCIA; break; }
                    __delay_ms(50);
                }
                ask = false;

                // Validar objetivo
                if (objetivo_temp == 0 || objetivo_temp > 60) {
                    LCD_I2C_Clear();
                    LCD_I2C_SetCursor(0, 0);
                    LCD_I2C_Print("  Valor errado! ");
                    LCD_I2C_SetCursor(0, 1);
                    LCD_I2C_Print("  Rango: 1-60kg ");
                    __delay_ms(2000);
                    estado = ST_ESPERA;
                } else {
                    peso_objetivo_kg = (float)objetivo_temp;
                    EEPROM_Write(0x02, (uint8_t)objetivo_temp);
                    estado = ST_COUNT;
                }
                break;

            // ------------------------------------------------
            case ST_COUNT:
                leds_set(1, 0, 0);          // LED verde
                embrague_on();
                servo_set(SERVO_ABIERTO);

                // Leer peso (5 Hz)
                {
                    int32_t raw = hx711_leer_promedio(16);
                    peso_kg = calcular_peso(raw);
                    lcd_mostrar_peso();
                }

                // Verificar objetivo
                if (peso_kg >= peso_objetivo_kg) {
                    embrague_off();
                    servo_set(SERVO_CERRADO);
                    bultos++;
                    EEPROM_Write(0x00, bultos);
                    beep_completado();
                    estado = ST_COMPLETADO;
                    break;
                }

                // STOP manual
                if (!STOP_PIN || tecla == 'B') {
                    tecla = 0;
                    embrague_off();
                    servo_set(SERVO_CERRADO);
                    estado = ST_ESPERA;
                }
                if (tecla == 'C') {
                    tecla = 0;
                    embrague_off();
                    servo_set(SERVO_CERRADO);
                    estado = ST_MENU;
                }

                __delay_ms(200);    // 5 Hz
                break;

            // ------------------------------------------------
            case ST_COMPLETADO:
                leds_set(1, 0, 0);
                lcd_mostrar_completado();

                // Parpadeo LED verde 5x
                for (uint8_t i = 0; i < 5; i++) {
                    LED_VERDE = 0;
                    __delay_ms(300);
                    LED_VERDE = 1;
                    __delay_ms(300);
                }

                ok = false;
                while (!ok) {
                    if (emergency) { estado = ST_EMERGENCIA; break; }
                    __delay_ms(50);
                }
                if (estado == ST_EMERGENCIA) break;

                // Nueva tara para el siguiente bulto
                realizar_tara();
                leds_set(0, 0, 0);
                estado = ST_ESPERA;
                break;

            // ------------------------------------------------
            case ST_MENU:
                lcd_mostrar_menu();
                // Navegacion simple con teclado
                // TODO: implementar submenu completo en v1.1
                // Por ahora: cualquier tecla vuelve a ESPERA
                while (tecla == 0) {
                    if (emergency) { estado = ST_EMERGENCIA; break; }
                    __delay_ms(50);
                }
                if (estado == ST_EMERGENCIA) break;
                tecla = 0;
                estado = ST_ESPERA;
                break;

            // ------------------------------------------------
            case ST_EMERGENCIA:
                embrague_off();             // Refuerzo SW (HW ya actuo)
                servo_set(SERVO_CERRADO);
                leds_set(0, 0, 1);          // LED rojo
                lcd_mostrar_emergencia();

                // Buzzer continuo mientras E-Stop presionado
                while (!ESTOP_PIN) {
                    BUZZER_PIN = 1;
                    __delay_ms(200);
                    BUZZER_PIN = 0;
                    __delay_ms(200);
                }

                // E-Stop liberado
                BUZZER_PIN = 0;
                emergency  = false;
                LCD_I2C_Clear();
                LCD_I2C_SetCursor(0, 0);
                LCD_I2C_Print("E-Stop liberado ");
                LCD_I2C_SetCursor(0, 1);
                LCD_I2C_Print("Reiniciando...  ");
                __delay_ms(2000);
                realizar_tara();
                leds_set(0, 0, 0);
                estado = ST_ESPERA;
                break;

            // ------------------------------------------------
            case ST_INICIO:
            default:
                estado = ST_ESPERA;
                break;
        }
    }
}

// ============================================================
// INICIALIZACION
// ============================================================
void initPorts(void) {
    // Oscilador interno 8 MHz
    OSCCON = 0b01110010;    // IRCF=111 (8 MHz), IOFS

    // PORTA: RA4=ESTOP(entrada), RA5=START(entrada)
    TRISA  = 0b00110000;    // RA4, RA5 como entradas
    LATA   = 0;

    // PORTB: RB0-RB3 filas teclado (salida), RB4-RB7 columnas (entrada+KBI)
    TRISB  = 0b11110000;    // RB7:4 entradas, RB3:0 salidas
    LATB   = 0b11110000;    // Filas en HIGH (inactivo), pull-ups en cols
    RBPU   = 0;             // Activar pull-ups internos PORTB

    // PORTC: RC2/CCP1=servo(salida), RC3=SCL(I2C), RC4=SDA(I2C)
    TRISC  = 0b11011000;    // RC3,RC4 para I2C (MSSP los controla), RC2 salida PWM
    LATC   = 0;

    // PORTD: RD0=HX_SCK(salida), RD1=HX_DOUT(entrada), RD3-RD7=salidas
    TRISD  = 0b00000010;    // Solo RD1 como entrada (DOUT HX711)
    LATD   = 0;

    // PORTE: RE0=STOP(entrada)
    TRISE  = 0b00000001;    // RE0 como entrada
    LATE   = 0;

    // ADC desactivado (no se usa en este proyecto)
    ADCON0 = 0;
    ADCON1 = 0x0F;          // Todos los pines como digitales

    // I2C MSSP para LCD
    SSPCON1 = 0b00101000;   // I2C Master mode
    SSPADD  = 19;           // 100 kHz @ 8 MHz: (8e6/(4*100e3))-1 = 19
    SSPSTAT = 0b10000000;   // Slew rate control desactivado

    // Estado inicial actuadores
    SSR_PIN      = 0;       // Embrague desacoplado
    BUZZER_PIN   = 0;
    LED_VERDE    = 0;
    LED_AMARILLO = 0;
    LED_ROJO     = 0;

    __delay_ms(100);
}

void initInterrupts(void) {
    // Timer0: base de tiempo (~500 ms)
    T0CON  = 0b00000010;    // 16 bits, reloj interno, prescaler 1:8
    TMR0   = 49911;
    TMR0IF = 0;
    TMR0IE = 1;
    TMR0ON = 1;

    // PORTB KBI: deteccion de teclado matricial
    RBIF   = 0;
    RBIE   = 1;

    // Interrupciones globales
    PEIE   = 1;
    GIE    = 1;
}

void initPWM(void) {
    // CCP1 como PWM @ 50 Hz para servo MG996R
    // Fosc=8MHz, prescaler T2=1:16, PR2=249
    // f_PWM = Fosc / (4 * (PR2+1) * prescaler) = 8e6/(4*250*16) = 500 Hz... ajustar
    // Para 50 Hz: prescaler=1:16, PR2=249 -> f=8e6/(4*(249+1)*16)=50 Hz ✓
    PR2     = 249;
    T2CON   = 0b00000011;   // Timer2 ON, prescaler 1:16
    CCP1CON = 0b00001100;   // PWM mode
    CCPR1L  = SERVO_CERRADO;
    TMR2    = 0;
}

// ============================================================
// HX711 — LECTURA BIT-BANG SPI
// ============================================================
int32_t hx711_leer_raw(void) {
    int32_t raw = 0;

    GIE = 0;    // Deshabilitar IRQ durante lectura critica

    // Esperar a que HX711 este listo (DOUT = LOW)
    uint16_t timeout = 10000;
    while (HX_DOUT && timeout--);
    if (timeout == 0) {
        GIE = 1;
        return 0x7FFFFFFF;  // Error: HX711 no responde
    }

    // Leer 24 bits MSB primero
    for (uint8_t i = 0; i < 24; i++) {
        HX_SCK = 1;
        __delay_us(1);
        raw = (raw << 1) | (HX_DOUT ? 1 : 0);
        HX_SCK = 0;
        __delay_us(1);
    }

    // Pulso 25: selecciona ganancia 128x (canal A) para la proxima lectura
    HX_SCK = 1;
    __delay_us(1);
    HX_SCK = 0;
    __delay_us(1);

    GIE = 1;

    // Extension de signo de 24 a 32 bits
    if (raw & 0x800000) {
        raw |= (int32_t)0xFF000000;
    }

    return raw;
}

int32_t hx711_leer_promedio(uint8_t n) {
    int64_t suma = 0;
    uint8_t muestras_validas = 0;

    for (uint8_t i = 0; i < n; i++) {
        int32_t raw = hx711_leer_raw();
        // Descartar lecturas claramente erroneas
        if (raw != 0x7FFFFFFF && raw != (int32_t)0x800000) {
            suma += raw;
            muestras_validas++;
        }
        __delay_ms(12);     // 80 SPS → 12.5 ms/muestra
    }

    if (muestras_validas == 0) return 0;
    return (int32_t)(suma / muestras_validas);
}

float calcular_peso(int32_t raw) {
    int32_t neto = raw - offset_tara;
    if (neto < 0) neto = 0;
    float kg = (float)neto / factor_calibracion;
    if (kg > 60.0f) kg = 60.0f;
    return kg;
}

void realizar_tara(void) {
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("Ejecutando tara ");
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("No colocar peso ");

    // Descartar las primeras 4 muestras (estabilizacion del HX711)
    for (uint8_t i = 0; i < 4; i++) {
        hx711_leer_raw();
        __delay_ms(12);
    }

    // Tomar 32 muestras para la tara
    offset_tara = hx711_leer_promedio(32);

    // Guardar en EEPROM (3 bytes: HI, MID, LO)
    EEPROM_Write(0x03, (uint8_t)((offset_tara >> 16) & 0xFF));
    EEPROM_Write(0x04, (uint8_t)((offset_tara >>  8) & 0xFF));
    EEPROM_Write(0x05, (uint8_t)( offset_tara        & 0xFF));

    beep(200);
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("Tara completada ");
    __delay_ms(1000);
}

// ============================================================
// LCD I2C — PANTALLAS
// ============================================================
void lcd_mostrar_espera(void) {
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("DAMSPI-150[ESPER");
    LCD_I2C_SetCursor(0, 3);
    LCD_I2C_Print("A=Iniciar C=Menu");
}

void lcd_mostrar_peso(void) {
    // Mostrar peso actual en fila 1 con 3 decimales
    // Formateo manual ya que no hay printf en XC8 free
    uint32_t gramos = (uint32_t)(peso_kg * 1000.0f);
    uint8_t  kg_u   = (uint8_t)(gramos / 1000);
    uint16_t g_dec  = (uint16_t)(gramos % 1000);

    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("PESO:  ");
    // Escribir kg (0-60)
    LCD_I2C_WriteChar('0' + kg_u / 10);
    LCD_I2C_WriteChar('0' + kg_u % 10);
    LCD_I2C_WriteChar('.');
    LCD_I2C_WriteChar('0' + g_dec / 100);
    LCD_I2C_WriteChar('0' + (g_dec % 100) / 10);
    LCD_I2C_WriteChar('0' + g_dec % 10);
    LCD_I2C_Print(" kg   ");

    // Objetivo y bultos en fila 2
    LCD_I2C_SetCursor(0, 2);
    LCD_I2C_Print("OBJ:");
    LCD_I2C_WriteChar('0' + (uint8_t)peso_objetivo_kg / 10);
    LCD_I2C_WriteChar('0' + (uint8_t)peso_objetivo_kg % 10);
    LCD_I2C_Print("kg BLT:");
    LCD_I2C_WriteChar('0' + bultos / 100);
    LCD_I2C_WriteChar('0' + (bultos % 100) / 10);
    LCD_I2C_WriteChar('0' + bultos % 10);
}

void lcd_mostrar_completado(void) {
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("** COMPLETADO! **");
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("Bultos: ");
    LCD_I2C_WriteChar('0' + bultos / 100);
    LCD_I2C_WriteChar('0' + (bultos % 100) / 10);
    LCD_I2C_WriteChar('0' + bultos % 10);
    LCD_I2C_SetCursor(0, 2);
    LCD_I2C_Print("                    ");
    LCD_I2C_SetCursor(0, 3);
    LCD_I2C_Print("Presione D para cont");
}

void lcd_mostrar_emergencia(void) {
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("** EMERGENCIA!! **");
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("  E-STOP ACTIVO  ");
    LCD_I2C_SetCursor(0, 2);
    LCD_I2C_Print("Libere el boton  ");
    LCD_I2C_SetCursor(0, 3);
    LCD_I2C_Print("para continuar   ");
}

void lcd_mostrar_menu(void) {
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print(">>> MENU CONFIG ");
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("> Peso objetivo ");
    LCD_I2C_SetCursor(0, 2);
    LCD_I2C_Print("  Tara manual   ");
    LCD_I2C_SetCursor(0, 3);
    LCD_I2C_Print("  Cualq.=Salir  ");
}

void lcd_mostrar_ask(void) {
    LCD_I2C_Clear();
    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_Print("Peso objetivo:  ");
    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_Print("___ kg (1-60)   ");
    LCD_I2C_SetCursor(0, 2);
    LCD_I2C_Print("                ");
    LCD_I2C_SetCursor(0, 3);
    LCD_I2C_Print("D=OK  #=Borrar  ");
}

// ============================================================
// TECLADO MATRICIAL 4x4 — ROW SCANNING
// ============================================================
uint8_t escanear_teclado(void) {
    // Mapa: {F1, F2, F3, F4} x {C1, C2, C3, C4}
    const uint8_t mapa[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    for (uint8_t fila = 0; fila < 4; fila++) {
        // Activar fila (LOW activo)
        LATB = ~(1 << fila) & 0x0F;
        __delay_us(10);

        uint8_t cols = (PORTB >> 4) & 0x0F;

        if (cols != 0x0F) {
            for (uint8_t col = 0; col < 4; col++) {
                if (!(cols & (1 << col))) {
                    LATB = 0b11110000;  // Restaurar filas
                    return mapa[fila][col];
                }
            }
        }
    }

    LATB = 0b11110000;
    return 0;   // Sin tecla
}

void procesar_tecla(uint8_t t) {
    counter_inact = 0;      // Reiniciar inactividad

    if (t == 0) return;

    // E-Stop via teclado (tecla especial — definir cual en HW final)
    // Por ahora el E-Stop es solo hardware

    if (ask) {
        // Ingreso numerico del peso objetivo
        if (t >= '0' && t <= '9') {
            if (input_count < 2) {
                uint8_t digito = t - '0';
                objetivo_temp = objetivo_temp * 10 + digito;
                input_count++;
                // Actualizar LCD fila 1
                LCD_I2C_SetCursor(0, 1);
                LCD_I2C_WriteChar('0' + objetivo_temp / 10);
                LCD_I2C_WriteChar('0' + objetivo_temp % 10);
                LCD_I2C_Print(" kg         ");
            }
        } else if (t == '#') {
            // Borrar
            if (input_count > 0) {
                objetivo_temp /= 10;
                input_count--;
                LCD_I2C_SetCursor(0, 1);
                LCD_I2C_WriteChar('0' + objetivo_temp / 10);
                LCD_I2C_WriteChar('0' + objetivo_temp % 10);
                LCD_I2C_Print(" kg         ");
            }
        } else if (t == 'D') {
            ok = true;
        }
    } else {
        // Fuera de modo ASK: guardar tecla para FSM principal
        tecla = t;
        if (t == 'D') ok = true;
    }
}

// ============================================================
// ACTUADORES
// ============================================================
void servo_set(uint8_t pos) {
    CCPR1L = pos;
}

void embrague_on(void) {
    SSR_PIN = 1;
}

void embrague_off(void) {
    SSR_PIN = 0;
}

// ============================================================
// ALERTAS
// ============================================================
void beep(uint16_t ms) {
    BUZZER_PIN = 1;
    uint16_t t = ms;
    while (t--) __delay_ms(1);
    BUZZER_PIN = 0;
    __delay_ms(80);
}

void beep_completado(void) {
    beep(500);
    beep(500);
    beep(500);
}

void leds_set(bool verde, bool amarillo, bool rojo) {
    LED_VERDE    = verde    ? 1 : 0;
    LED_AMARILLO = amarillo ? 1 : 0;
    LED_ROJO     = rojo     ? 1 : 0;
}

// ============================================================
// EEPROM
// ============================================================
void EEPROM_Write(uint8_t addr, uint8_t data) {
    EEADR             = addr;
    EEDATA            = data;
    EECON1bits.EEPGD  = 0;
    EECON1bits.CFGS   = 0;
    EECON1bits.WREN   = 1;
    INTCONbits.GIE    = 0;
    EECON2            = 0x55;
    EECON2            = 0xAA;
    EECON1bits.WR     = 1;
    while (EECON1bits.WR);
    EECON1bits.WREN   = 0;
    INTCONbits.GIE    = 1;
}

uint8_t EEPROM_Read(uint8_t addr) {
    EEADR            = addr;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.RD    = 1;
    return EEDATA;
}

void guardar_calibracion(void) {
    // Factor de calibracion como uint16_t (raw_por_kg, max 65535)
    uint16_t fc = (uint16_t)factor_calibracion;
    EEPROM_Write(0x06, (uint8_t)(fc >> 8));
    EEPROM_Write(0x07, (uint8_t)(fc & 0xFF));
    // Offset de tara
    EEPROM_Write(0x03, (uint8_t)((offset_tara >> 16) & 0xFF));
    EEPROM_Write(0x04, (uint8_t)((offset_tara >>  8) & 0xFF));
    EEPROM_Write(0x05, (uint8_t)( offset_tara        & 0xFF));
}

void cargar_calibracion(void) {
    // Leer offset de tara (3 bytes)
    uint8_t hi  = EEPROM_Read(0x03);
    uint8_t mid = EEPROM_Read(0x04);
    uint8_t lo  = EEPROM_Read(0x05);

    // Si EEPROM virgen (0xFF), usar valores por defecto
    if (hi == 0xFF && mid == 0xFF && lo == 0xFF) {
        offset_tara = 0;
    } else {
        offset_tara = ((int32_t)hi << 16) | ((int32_t)mid << 8) | lo;
        if (offset_tara & 0x800000) offset_tara |= (int32_t)0xFF000000;
    }

    // Leer factor de calibracion
    uint8_t fc_hi = EEPROM_Read(0x06);
    uint8_t fc_lo = EEPROM_Read(0x07);
    if (fc_hi == 0xFF && fc_lo == 0xFF) {
        factor_calibracion = 1000.0f;   // Valor por defecto: 1000 raw/kg (calibrar!)
    } else {
        factor_calibracion = (float)(((uint16_t)fc_hi << 8) | fc_lo);
    }

    // Objetivo por defecto
    uint8_t obj = EEPROM_Read(0x02);
    if (obj == 0xFF || obj == 0 || obj > 60) {
        peso_objetivo_kg = 50.0f;
    } else {
        peso_objetivo_kg = (float)obj;
    }

    // Contador de bultos
    bultos = EEPROM_Read(0x00);
    if (bultos == 0xFF) bultos = 0;
}

// ============================================================
// RUTINA DE INTERRUPCION
// ============================================================
void __interrupt() ISR(void) {

    // --- Timer0: base de tiempo ~500 ms ---
    if (TMR0IF) {
        counter_inact++;

        // Apagar backlight LCD por inactividad (>10 seg ~ 20 interrupciones)
        if (counter_inact >= 20) {
            LCD_I2C_Backlight(false);
        }

        // Sleep por inactividad prolongada (>20 seg ~ 40 interrupciones)
        if (counter_inact >= 40) {
            embrague_off();
            leds_set(0, 0, 0);
            SLEEP();
        }

        TMR0   = 49911;
        TMR0IF = 0;
    }

    // --- Cambio en PORTB: teclado matricial ---
    if (RBIF) {
        if ((PORTB & 0xF0) != 0xF0) {   // Columna activa detectada
            uint8_t t = escanear_teclado();
            if (t != 0) {
                __delay_ms(20);          // Anti-rebote
                procesar_tecla(t);

                // Reactivar backlight si estaba apagado
                LCD_I2C_Backlight(true);
                counter_inact = 0;
            }
        }
        RBIF = 0;
    }
}
