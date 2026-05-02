# Firmware DAMSPI-150 — PIC18F4550

## Requisitos

| Herramienta | Versión mínima |
|-------------|---------------|
| MPLAB X IDE | 6.0 |
| XC8 Compiler | 3.0 |
| Programador | PICkit 3 o PICkit 4 |

## Compilar

1. Abrir MPLAB X IDE
2. **File → Open Project** → seleccionar carpeta `DAMSPI150.X/`
3. Verificar Device: `PIC18F4550`, Compiler: `XC8`
4. **Clean and Build** (Ctrl+Shift+F11)
5. El `.hex` queda en `dist/default/production/`

## Programar

Conexión ICSP (5 pines):

```
PICkit 4    →   PIC18F4550
─────────────────────────
MCLR (VPP)  →   Pin 1  (MCLR/VPP)
VDD         →   Pin 11 (VDD +5V)
GND         →   Pin 12 (VSS GND)
PGD (ICSPD) →   Pin 40 (RB7/PGD)
PGC (ICSPC) →   Pin 39 (RB6/PGC)
```

## Calibración del Sistema de Pesaje

**Primera vez o tras cambiar celdas de carga:**

1. Dejar la plataforma de pesaje completamente vacía
2. Energizar el sistema → ejecutar tara automática al inicio
3. Colocar una masa de referencia conocida (ej. 5 kg certificados)
4. Leer el valor raw del HX711 (via UART debug en RC6/RC7)
5. Calcular: `factor_calibracion = (raw_con_masa - offset_tara) / masa_kg`
6. Actualizar la constante en el firmware y recompilar, O usar la opción de calibración del menú LCD

## Estructura del Firmware

```
DAMSPI150.c         ← Archivo principal (main + ISR + toda la lógica)
LibLCD_I2C_XC8.h    ← Driver LCD 20x4 via I2C PCF8574
```

## Mapa EEPROM

| Dirección | Contenido |
|-----------|-----------|
| 0x00 | Contador de bultos |
| 0x01 | Reservado |
| 0x02 | Peso objetivo (kg, entero) |
| 0x03 | offset_tara byte HI |
| 0x04 | offset_tara byte MID |
| 0x05 | offset_tara byte LO |
| 0x06 | factor_calibracion byte HI |
| 0x07 | factor_calibracion byte LO |

## Pines del PIC18F4550

Ver tabla completa en `08_Electronica/GUIA_ELECTRONICA.md §5.2`
