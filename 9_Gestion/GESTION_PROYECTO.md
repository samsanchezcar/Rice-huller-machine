# GESTIÓN DEL PROYECTO — DAMSPI-150
## EDT Detallado · Gantt · Gestión de Proveedores y Compras
### Responsable de Gestión: Samuel D. Sánchez C.

---

## 1. RESUMEN DE GESTIÓN

| Parámetro | Valor |
|-----------|-------|
| Proyecto | DAMSPI-150 — Descascaradora de Arroz Modular Semiautomática con Pesaje Integrado |
| Duración total | 14 semanas (3 Feb – 30 May 2026) |
| Presupuesto disponible | $7.000.000 COP (aportado por solicitante) |
| Presupuesto estimado actual | ~$5.980.000 COP |
| Margen de contingencia | ~$1.020.000 COP (~14.6%) |
| Responsable de gestión | Samuel D. Sánchez C. |
| Método de seguimiento | Reunión semanal + actualización GANTT + bitácoras |
| Herramientas de gestión | Excel (GANTT + BOM) + GitHub/Drive (repositorio) |

---

## 2. ESTRUCTURA DE DESGLOSE DE TRABAJO (EDT / WBS)

### Nivel 1 — DAMSPI-150

```
DAMSPI-150
├── 1. GESTIÓN DEL PROYECTO
├── 2. INGENIERÍA DE SISTEMAS Y REQUISITOS
├── 3. DISEÑO MECÁNICO
│   ├── 3.1 Módulo 1 — Potencia y Transmisión
│   ├── 3.2 Módulo 2 — Descascarillado
│   ├── 3.3 Módulo 3 — Control y Pesaje (chasis)
│   └── 3.4 Módulo 4 — Chasis Principal y Tolvas
├── 4. DISEÑO ELÉCTRICO (POTENCIA)
├── 5. DISEÑO ELECTRÓNICO (CONTROL)
├── 6. ADQUISICIONES Y MANUFACTURA
│   ├── 6.1 Gestión de proveedores
│   ├── 6.2 Compras y tiempos de espera
│   └── 6.3 Manufactura aditiva y taller externo
├── 7. MONTAJE E INTEGRACIÓN
├── 8. VALIDACIÓN Y PRUEBAS
└── 9. DOCUMENTACIÓN Y ENTREGA FINAL
```

---

### EDT COMPLETO — Nivel 3 (todas las tareas)

#### 1. GESTIÓN DEL PROYECTO

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 1.1 | Reunión de lanzamiento y definición de roles | Todos | S1 | S1 | 1 sem |
| 1.2 | Configuración del repositorio (Drive + estructura) | Samuel | S1 | S1 | 0.5 sem |
| 1.3 | Elaboración del acuerdo con solicitante (AS) | Todos | S1 | S2 | 1 sem |
| 1.4 | Elaboración del contrato social (CS) | Todos | S1 | S2 | 1 sem |
| 1.5 | Definición del presupuesto inicial y BOM v0 | Samuel | S2 | S2 | 0.5 sem |
| 1.6 | Reunión semanal de seguimiento | Todos | S1 | S14 | 14 sem |
| 1.7 | Actualización semanal del GANTT | Samuel | S1 | S14 | 14 sem |
| 1.8 | Actualización semanal de bitácoras individuales | Todos | S1 | S14 | 14 sem |
| 1.9 | Actualización del registro de proveedores | Samuel | S3 | S12 | 10 sem |
| 1.10 | Control de presupuesto vs. gasto real | Samuel | S3 | S14 | 12 sem |
| 1.11 | Revisión de riesgos y plan de contingencia | Samuel | S4 | S4 | 1 sem |
| 1.12 | Comunicación con solicitante (actualizaciones) | Samuel | S4 | S13 | 10 sem |

#### 2. INGENIERÍA DE SISTEMAS Y REQUISITOS

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 2.1 | Revisión bibliográfica y estado del arte | Todos | S1 | S3 | 3 sem |
| 2.2 | Definición de requerimientos técnicos (PDS) | Nicolás + Samuel | S2 | S3 | 2 sem |
| 2.3 | Definición de restricciones y normas aplicables | Nicolás + Samuel | S2 | S3 | 1 sem |
| 2.4 | Diseño de la arquitectura de módulos | Nicolás | S3 | S4 | 2 sem |
| 2.5 | Diagramas de caja negra y caja gris | Nicolás + Gabriel | S3 | S5 | 3 sem |
| 2.6 | Análisis funcional del sistema (QFD simplificado) | Nicolás + Samuel | S4 | S5 | 2 sem |
| 2.7 | Redacción del Informe Parte I | Todos | S3 | S4 | 2 sem |
| 2.8 | Entrega y sustentación Informe Parte I | Todos | S4 | S4 | 0.5 sem |

#### 3. DISEÑO MECÁNICO

##### 3.1 Módulo 1 — Potencia y Transmisión

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 3.1.1 | Selección de tipo de transmisión (poleas en V) | Nicolás | S3 | S4 | 2 sem |
| 3.1.2 | Cálculo de relación de transmisión y dimensionado poleas | Nicolás | S4 | S5 | 2 sem |
| 3.1.3 | Selección del eje secundario: material, diámetros, longitud | Sebastián | S4 | S6 | 3 sem |
| 3.1.4 | Cálculo de rodamientos para eje secundario | Sebastián | S5 | S6 | 2 sem |
| 3.1.5 | Diseño del soporte del alternador (optimización topológica) | Andrés | S5 | S7 | 3 sem |
| 3.1.6 | Diseño de la carcasa del Módulo 1 (CAD Onshape) | Andrés | S6 | S8 | 3 sem |
| 3.1.7 | Diseño del sistema de acoplamiento embrague-eje | Nicolás + Sebastián | S5 | S7 | 3 sem |
| 3.1.8 | Planos de fabricación Módulo 1 | Nicolás | S8 | S9 | 2 sem |

##### 3.2 Módulo 2 — Descascarillado

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 3.2.1 | Investigación de parámetros de rodillos PU (Solagro) | Nicolás | S3 | S5 | 3 sem |
| 3.2.2 | Cálculo de fuerzas de descascarillado (presión rodillos) | Nicolás | S5 | S6 | 2 sem |
| 3.2.3 | Diseño del sistema de ajuste de la separación entre rodillos | Nicolás | S5 | S7 | 3 sem |
| 3.2.4 | Diseño del ventilador centrífugo para separación cáscara | Andrés | S6 | S8 | 3 sem |
| 3.2.5 | Diseño del Sin Fín alimentador (o compuerta de gaveta) | Sebastián | S6 | S8 | 3 sem |
| 3.2.6 | Diseño de la tolva de entrada y compuerta servomotor | Andrés | S6 | S8 | 3 sem |
| 3.2.7 | CAD Onshape Módulo 2 completo | Andrés + Nicolás | S7 | S9 | 3 sem |
| 3.2.8 | Planos de fabricación Módulo 2 | Nicolás | S9 | S10 | 2 sem |

##### 3.3 Módulo 3 — Carcasa del Panel de Control

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 3.3.1 | Diseño de la carcasa del panel LCD + teclado + pilotos | Andrés | S7 | S8 | 2 sem |
| 3.3.2 | Soporte plataforma de pesaje (celdas tipo S) | Andrés | S7 | S8 | 2 sem |
| 3.3.3 | Optimización topológica soportes celdas + plataforma | Andrés | S6 | S8 | 3 sem |
| 3.3.4 | Diseño de puntos de conexión rápida (Módulo 3 ↔ 4) | Nicolás | S8 | S9 | 2 sem |
| 3.3.5 | CAD Onshape Módulo 3 (carcasa) | Andrés | S8 | S9 | 2 sem |

##### 3.4 Módulo 4 — Chasis Principal

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 3.4.1 | Diseño estructural del chasis (perfiles 40×40 mm) | Nicolás | S5 | S7 | 3 sem |
| 3.4.2 | Cálculo de cargas sobre el chasis (FEM simplificado) | Sebastián | S6 | S7 | 2 sem |
| 3.4.3 | Diseño del sistema de ruedas + bloqueo | Andrés | S7 | S8 | 2 sem |
| 3.4.4 | Diseño de los pasadores de conexión rápida entre módulos | Nicolás | S7 | S8 | 2 sem |
| 3.4.5 | CAD Onshape Módulo 4 completo | Nicolás + Andrés | S7 | S9 | 3 sem |
| 3.4.6 | Planos de fabricación Módulo 4 | Nicolás | S9 | S10 | 2 sem |

#### 4. DISEÑO ELÉCTRICO (POTENCIA)

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 4.1 | Cálculo de potencia eléctrica requerida total | Santiago | S4 | S4 | 1 sem |
| 4.2 | Selección del alternador: tipo, potencia, acoplamiento | Santiago | S4 | S5 | 2 sem |
| 4.3 | Diseño circuito rectificador + regulador | Santiago | S5 | S6 | 2 sem |
| 4.4 | Diseño circuito Boost DC-DC (14V→24V) | Santiago | S5 | S6 | 2 sem |
| 4.5 | Diseño circuito Buck DC-DC (24V→5V) | Santiago + Samuel | S5 | S6 | 2 sem |
| 4.6 | Diseño del sistema de carga de batería (XH-M603) | Santiago | S6 | S7 | 2 sem |
| 4.7 | Dimensionado de cables y secciones por tramo | Santiago | S7 | S8 | 2 sem |
| 4.8 | Diseño del cableado de potencia entre módulos | Santiago | S8 | S9 | 2 sem |
| 4.9 | Diseño del circuito de protecciones (fusibles, E-Stop) | Santiago + Samuel | S7 | S8 | 2 sem |
| 4.10 | Documentación guía eléctrica v1.0 | Santiago | S8 | S9 | 2 sem |

#### 5. DISEÑO ELECTRÓNICO (CONTROL)

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 5.1 | Definición de la arquitectura de control | Samuel + Gabriel | S4 | S4 | 1 sem |
| 5.2 | Asignación de pines PIC18F4550 | Samuel | S4 | S5 | 1 sem |
| 5.3 | Diseño esquemático completo (Módulo 3) | Gabriel | S5 | S7 | 3 sem |
| 5.4 | Diseño del circuito de interfaz SSR + embrague | Gabriel | S5 | S6 | 2 sem |
| 5.5 | Diseño del circuito de pilotos LED (drivers 2N2222) | Gabriel | S5 | S6 | 1 sem |
| 5.6 | Diseño circuito de celdas de carga (puente Wheatstone → HX711) | Samuel | S5 | S6 | 2 sem |
| 5.7 | Diseño circuito LCD 20×4 I2C (PCF8574) | Gabriel | S5 | S6 | 1 sem |
| 5.8 | Diseño circuito teclado matricial 4×4 (PORTB) | Gabriel | S5 | S6 | 1 sem |
| 5.9 | Revisión y validación del esquemático | Samuel + Gabriel | S7 | S7 | 1 sem |
| 5.10 | Firmware: initPorts(), initInterrupts(), initLCD_I2C() | Samuel | S6 | S7 | 2 sem |
| 5.11 | Firmware: driver HX711 (hx711_leer_raw, promedio, tara) | Samuel | S7 | S8 | 2 sem |
| 5.12 | Firmware: driver LCD I2C y teclado matricial | Samuel | S7 | S8 | 2 sem |
| 5.13 | Firmware: máquina de estados principal (FSM) | Samuel | S8 | S9 | 2 sem |
| 5.14 | Firmware: control SSR embrague + servo MG996R | Samuel | S8 | S9 | 2 sem |
| 5.15 | Firmware: EEPROM — guardar/restaurar calibración | Samuel | S9 | S9 | 1 sem |
| 5.16 | Firmware: alertas (buzzer, pilotos LED) | Samuel | S9 | S10 | 1 sem |
| 5.17 | Firmware: E-Stop hardware y software | Samuel + Gabriel | S9 | S10 | 1 sem |
| 5.18 | Prueba de firmware en banco (sin mecánica) | Samuel + Gabriel | S10 | S10 | 1 sem |
| 5.19 | Documentación guía electrónica v2.0 | Samuel | S8 | S10 | 3 sem |

#### 6. ADQUISICIONES Y MANUFACTURA

##### 6.1 Gestión de Proveedores (SAMUEL — responsable único)

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 6.1.1 | Contacto inicial con Solagro Colombia (rodillos, pulidora) | Samuel | S3 | S3 | 0.5 sem |
| 6.1.2 | Solicitud de cotización formal a Solagro (rodillos PU Ø80mm + pulidora horizontal) | Samuel | S3 | S4 | 1 sem |
| 6.1.3 | Contacto y cotización: embrague DLD6-05 (MercadoLibre / proveedor local) | Samuel | S3 | S4 | 1 sem |
| 6.1.4 | Contacto y cotización: batería LiFePO4 24V 5Ah (AliExpress + alternativa local) | Samuel | S3 | S4 | 1 sem |
| 6.1.5 | Cotización: alternador de motocicleta (repuestos motos Bogotá + MercadoLibre) | Samuel | S4 | S4 | 0.5 sem |
| 6.1.6 | Cotización: perfiles acero 40×40 + rodamientos + poleas (ferretería industrial) | Samuel | S4 | S5 | 1 sem |
| 6.1.7 | Contacto taller externo UNAL para mecanizado ejes | Samuel + Nicolás | S4 | S5 | 1 sem |
| 6.1.8 | Cotización: PCB fabricada (JLCPCB/PCBWay o local) | Gabriel + Samuel | S6 | S7 | 2 sem |
| 6.1.9 | Cotización: PIC18F4550 + HX711 + LCD 20×4 I2C (AliExpress, Naylampmechatronics) | Samuel | S4 | S5 | 1 sem |
| 6.1.10 | Cotización: SSR 24VDC, servo MG996R, pilotos industriales, E-Stop | Samuel | S4 | S5 | 1 sem |
| 6.1.11 | Comparación de cotizaciones y selección de proveedores definitivos | Samuel | S5 | S5 | 0.5 sem |
| 6.1.12 | Aprobación de compras con el equipo (reunión de compras) | Samuel + Todos | S5 | S5 | 0.5 sem |
| 6.1.13 | Registro y actualización del REGISTRO_PROVEEDORES.md | Samuel | S3 | S14 | Continuo |
| 6.1.14 | Seguimiento semanal a pedidos pendientes | Samuel | S5 | S11 | 7 sem |
| 6.1.15 | Recepción e inspección de componentes (verificar contra BOM) | Samuel | S6 | S12 | Continuo |
| 6.1.16 | Informe semanal de compras al equipo (WhatsApp/Discord) | Samuel | S5 | S12 | 8 sem |

##### 6.2 Compras y Tiempos de Espera (SAMUEL)

| ID | Componente | Semana Pedido | Tiempo Espera Est. | Semana Llegada | Estado |
|----|-----------|--------------|-------------------|---------------|--------|
| 6.2.1 | Rodillos PU Ø80mm + pulidora (Solagro) | S4 | 3–4 semanas | S7–S8 | Gestionar S3 |
| 6.2.2 | Batería LiFePO4 24V/5Ah (AliExpress) | S4 | 4–6 semanas | S8–S10 | ⚠️ Urgente |
| 6.2.3 | Embrague DLD6-05 24V (local/MercadoLibre) | S4 | 1–2 semanas | S5–S6 | — |
| 6.2.4 | PIC18F4550, HX711, LCD 20×4 I2C (AliExpress) | S4 | 3–5 semanas | S7–S9 | ⚠️ Urgente |
| 6.2.5 | Teclado matricial 4×4, SSR, servo MG996R (local) | S5 | 1–2 semanas | S6–S7 | — |
| 6.2.6 | Alternador de motocicleta (local Bogotá) | S5 | 1 semana | S6 | — |
| 6.2.7 | Celda de carga tipo S ×4 (AliExpress) | S4 | 3–5 semanas | S7–S9 | ⚠️ Urgente |
| 6.2.8 | Perfiles acero + poleas + rodamientos (local) | S6 | 1 semana | S7 | — |
| 6.2.9 | Componentes electrónicos locales (resistencias, condensadores, transistores) | S5 | 1–3 días | S5 | — |
| 6.2.10 | PCB fabricada (JLCPCB — envío express) | S8 | 1–2 semanas | S9–S10 | Requiere esquemático S7 |
| 6.2.11 | Caja de control IP54 + prensaestopas | S6 | 1 semana | S7 | — |
| 6.2.12 | Cable eléctrico + conectores industriales | S6 | 1–3 días | S6 | — |
| 6.2.13 | Impresión 3D piezas PETG/PLA+ (taller externo o campus) | S9 | 1–2 semanas | S10–S11 | Requiere CAD S8 |

> **⚠️ ALERTA DE RUTA CRÍTICA**: Los ítems 6.2.1 (rodillos Solagro), 6.2.2 (batería AliExpress), 6.2.4 (PIC+HX711+LCD) y 6.2.7 (celdas de carga) tienen los tiempos de espera más largos. Samuel debe iniciar la gestión de estos en la **Semana 3** para garantizar disponibilidad en Semana 8–9 (inicio de montaje).

##### 6.3 Manufactura — Piezas Impresas y Taller Externo

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 6.3.1 | Optimización topológica soportes celdas de carga | Andrés | S6 | S8 | 3 sem |
| 6.3.2 | Optimización topológica soporte alternador | Andrés | S6 | S7 | 2 sem |
| 6.3.3 | Preparación archivos STL para impresión 3D (todos los módulos) | Andrés | S9 | S9 | 1 sem |
| 6.3.4 | Gestión de impresión 3D en campus o taller externo | Andrés + Samuel | S9 | S10 | 2 sem |
| 6.3.5 | Post-procesado de piezas impresas (insertos calor, lijado) | Andrés | S10 | S11 | 2 sem |
| 6.3.6 | Coordinación taller externo para mecanizado eje secundario | Nicolás + Samuel | S6 | S8 | 3 sem |
| 6.3.7 | Mecanizado de ejes, chavetas, rosca (taller externo UNAL) | Taller externo | S8 | S9 | 2 sem |
| 6.3.8 | Soldadura del chasis (taller externo) | Taller externo | S9 | S10 | 2 sem |
| 6.3.9 | Limpieza y pintura del chasis | Andrés + Sebastián | S10 | S11 | 1 sem |

#### 7. MONTAJE E INTEGRACIÓN

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 7.1 | Ensamble Módulo 1 (motor + alternador + transmisión) | Nicolás + Santiago | S10 | S11 | 2 sem |
| 7.2 | Ensamble Módulo 2 (rodillos + ventilador + Sin Fín) | Nicolás + Sebastián | S10 | S11 | 2 sem |
| 7.3 | Ensamble Módulo 3 — Electrónica (PCB + sensores + panel) | Samuel + Gabriel | S10 | S11 | 2 sem |
| 7.4 | Instalación del sistema de pesaje (celdas + HX711 + plataforma) | Samuel | S11 | S11 | 1 sem |
| 7.5 | Cableado eléctrico de potencia entre módulos | Santiago + Samuel | S11 | S12 | 2 sem |
| 7.6 | Instalación del embrague + SSR + cableado 24V | Samuel + Santiago | S11 | S11 | 1 sem |
| 7.7 | Ensamble Módulo 4 (chasis + ruedas + pasadores) | Nicolás + Andrés | S10 | S11 | 2 sem |
| 7.8 | Integración de los 4 módulos sobre el chasis | Todos | S11 | S12 | 2 sem |
| 7.9 | Primera puesta en marcha (sin arroz) | Todos | S12 | S12 | 1 sem |
| 7.10 | Ajuste de rodillos y calibración mecánica | Nicolás + Sebastián | S12 | S12 | 1 sem |

#### 8. VALIDACIÓN Y PRUEBAS

| ID | Prueba | Responsable | Semana Inicio | Semana Fin | Duración |
|----|--------|-------------|--------------|-----------|----------|
| 8.1 | P1: Calibración sistema de pesaje (HX711 + celdas) | Samuel | S12 | S12 | 1 sem |
| 8.2 | P2: Prueba de tara dinámica con motor encendido | Samuel | S12 | S12 | 0.5 sem |
| 8.3 | P3: Prueba de paro automático por peso objetivo | Samuel + Gabriel | S12 | S12 | 0.5 sem |
| 8.4 | P4: Prueba E-Stop hardware | Samuel + Santiago | S12 | S12 | 0.5 sem |
| 8.5 | P5: Autonomía de la batería | Santiago | S12 | S13 | 1 sem |
| 8.6 | P6: Eficiencia de descascarillado (% granos rotos) | Nicolás + Sebastián | S12 | S13 | 2 sem |
| 8.7 | P7: Medición de capacidad (kg/h real) | Todos | S13 | S13 | 1 sem |
| 8.8 | P8: Ruido (dB) y vibración | Nicolás + Sebastián | S13 | S13 | 0.5 sem |
| 8.9 | P9: Prueba de desmontaje/montaje completo (≤ 60 min) | Todos | S13 | S13 | 0.5 sem |
| 8.10 | P10: Temperatura PCB y componentes eléctricos (1h continua) | Samuel + Santiago | S13 | S13 | 1 sem |
| 8.11 | Registro de resultados y análisis de desviaciones | Samuel + Nicolás | S13 | S13 | 1 sem |
| 8.12 | Correcciones post-prueba (ajustes mecánicos + firmware) | Todos | S13 | S13 | 1 sem |
| 8.13 | Grabación del video de demostración | Todos | S13 | S13 | 0.5 sem |

#### 9. DOCUMENTACIÓN Y ENTREGA FINAL

| ID | Tarea | Responsable | Semana Inicio | Semana Fin | Duración |
|----|-------|-------------|--------------|-----------|----------|
| 9.1 | Redacción Informe Parte II (diseño detallado) | Todos | S6 | S8 | 3 sem |
| 9.2 | Entrega y sustentación Informe Parte II | Todos | S8 | S8 | 0.5 sem |
| 9.3 | Redacción Informe Final Parte III | Todos | S12 | S14 | 3 sem |
| 9.4 | Planos de fabricación finales (PDF/DWG) | Nicolás | S10 | S12 | 3 sem |
| 9.5 | Manual de usuario del DAMSPI-150 | Samuel + Nicolás | S13 | S14 | 2 sem |
| 9.6 | Manual de mantenimiento preventivo | Santiago + Nicolás | S13 | S14 | 2 sem |
| 9.7 | Actualización BOM final con precios reales | Samuel | S13 | S14 | 1 sem |
| 9.8 | Preparación de la presentación final | Todos | S13 | S14 | 2 sem |
| 9.9 | Entrega final y demostración al solicitante | Todos | S14 | S14 | 1 día |
| 9.10 | Cierre del repositorio y archivo definitivo | Samuel | S14 | S14 | 0.5 sem |

---

## 3. GANTT — CRONOGRAMA GENERAL (Semanas 1–14)

> **Referencia**: El archivo Excel `03_Cronograma_GANTT/GANTT_Descascaradora_v2.xlsx` contiene el GANTT original. La versión actualizada refleja el EDT completo de la sección 2.

```
TAREA / FASE                          S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14
─────────────────────────────────────────────────────────────────────────────────────────────
1. GESTIÓN DEL PROYECTO
  1.1 Reunión semanal                  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██
  1.7 Actualización GANTT + BOM        ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██
  1.8 Bitácoras individuales           ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██  ██

2. REQUISITOS Y SISTEMAS
  2.1 Revisión bibliográfica           ██  ██  ██
  2.2-2.6 Req. + arquitectura             ██  ██  ██  ██
  2.7-2.8 INFORME PARTE I                     ██  ██★

3.1 MÓDULO 1 MECÁNICO
  3.1.1-3.1.2 Transmisión                     ██  ██  ██
  3.1.3-3.1.4 Eje secundario                  ██  ██  ██  ██
  3.1.5-3.1.7 Soporte alt.+embrague               ██  ██  ██  ██
  3.1.6-3.1.8 CAD + planos                            ██  ██  ██  ██

3.2 MÓDULO 2 MECÁNICO
  3.2.1-3.2.2 Rodillos PU                     ██  ██  ██
  3.2.3-3.2.6 Ajustador+ventilador+Sin Fín        ██  ██  ██  ██
  3.2.7-3.2.8 CAD + planos                                ██  ██  ██

3.3-3.4 MÓDULOS 3-4 MECÁNICO
  Carcasa panel + soporte celdas                       ██  ██  ██
  Chasis + pasadores + ruedas                  ██  ██  ██  ██
  CAD Onshape + planos                                 ██  ██  ██

4. DISEÑO ELÉCTRICO (POTENCIA)
  4.1-4.5 Alternador+Boost+Buck                ██  ██  ██  ██
  4.6-4.9 Batería+XH-M603+cables                   ██  ██  ██  ██
  4.10 Guía eléctrica v1.0                                ██  ██

5. DISEÑO ELECTRÓNICO (CONTROL)
  5.1-5.2 Arquitectura + pines                 ██
  5.3-5.9 Esquemático completo                     ██  ██  ██  ██
  5.10-5.12 Firmware base (init+LCD+HX711)         ██  ██  ██
  5.13-5.17 Firmware FSM + control                     ██  ██  ██
  5.18 Prueba firmware en banco                            ██
  5.19 Guía electrónica v2.0                       ██  ██  ██

6. ADQUISICIONES Y MANUFACTURA
  6.1.1-6.1.5 Contacto Solagro+proveed.       ██  ██
  6.1.6-6.1.10 Cotizaciones electrónica        ██  ██
  6.1.11-6.1.12 Selección + aprobación             ██
  ⚠️ PEDIDO RODILLOS SOLAGRO                   ██  (entrega S7-S8)
  ⚠️ PEDIDO BATERÍA ALIEXPRESS                  ██  (entrega S8-S10)
  ⚠️ PEDIDO CELDAS DE CARGA                     ██  (entrega S7-S9)
  ⚠️ PEDIDO PIC+HX711+LCD I2C                   ██  (entrega S7-S9)
  Pedidos locales (electrónica general)            ██  ██
  Pedidos eléctricos (cables, conectores)          ██  ██
  6.1.14-6.1.16 Seguimiento pedidos                ██  ██  ██  ██  ██  ██  ██
  6.1.15 Recepción e inspección comp.               ██  ██  ██  ██  ██  ██
  6.3.1-6.3.5 Manufactura aditiva FDM                              ██  ██  ██
  6.3.6-6.3.9 Taller externo (ejes+chasis)                  ██  ██  ██  ██

7. MONTAJE E INTEGRACIÓN
  7.1-7.2 Ensamble Módulos 1 y 2                                       ██  ██
  7.3-7.6 Electrónica + cableado                                       ██  ██
  7.7-7.8 Chasis + integración 4 módulos                               ██  ██
  7.9-7.10 Primera puesta en marcha                                        ██

8. VALIDACIÓN Y PRUEBAS
  8.1-8.6 Pruebas de pesaje+E-Stop                                         ██  ██
  8.7-8.13 Pruebas mecánicas+video                                              ██

9. DOCUMENTACIÓN Y ENTREGA
  9.1-9.2 INFORME PARTE II                                 ██  ██★
  9.3-9.8 Informe Final + manual + video                                   ██  ██  ██
  9.9 ENTREGA FINAL                                                              ██★
─────────────────────────────────────────────────────────────────────────────────────────────
★ = Hito / Entregable clave       ⚠️ = Ítem en ruta crítica (no puede retrasarse)
```

### Hitos Críticos del Proyecto

| Hito | Semana | Descripción |
|------|--------|-------------|
| M1 | S4 | Entrega y aprobación Informe Parte I |
| M2 | S4 | Todos los pedidos de largo plazo realizados (AliExpress) |
| M3 | S5 | Cotizaciones Solagro confirmadas + decisión de compra |
| M4 | S7–S8 | Llegada de componentes críticos (celdas, PIC, LCD, rodillos) |
| M5 | S8 | Entrega Informe Parte II — Diseño detallado completo |
| M6 | S9–S10 | Todos los componentes disponibles para montaje |
| M7 | S12 | Sistema ensamblado + primera puesta en marcha |
| M8 | S13 | Pruebas de validación completas + video grabado |
| M9 | S14 | Entrega final al solicitante |

---

## 4. GESTIÓN DE RIESGOS

| ID | Riesgo | Probabilidad | Impacto | Estrategia de Mitigación | Responsable |
|----|--------|-------------|---------|--------------------------|-------------|
| R1 | Retraso en entrega AliExpress (batería, celdas, PIC) | Alta | Alto | Hacer pedido en S3–S4; tener proveedor local alternativo | Samuel |
| R2 | Solagro no tiene stock de rodillos Ø80mm | Media | Muy alto | Contactar en S3; buscar alternativas (importar, otro proveedor) | Samuel + Nicolás |
| R3 | Taller externo no puede mecanizar ejes a tiempo | Media | Alto | Reservar cita en S5; tener alternativa de taller privado | Samuel + Nicolás |
| R4 | Firmware más complejo de lo estimado (HX711 + LCD I2C) | Media | Medio | Iniciar en S5; usar librerías probadas; pruebas paralelas | Samuel |
| R5 | PCB con errores (requiere nueva fabricación) | Media | Alto | Revisión doble del esquemático antes de fabricar; prototipar en protoboard primero | Gabriel + Samuel |
| R6 | Presupuesto insuficiente para rodillos + pulidora | Media | Alto | Renegociar con solicitante; buscar alternativa técnica | Samuel + Todos |
| R7 | Embrague DLD6-05 no disponible en Colombia | Baja | Muy alto | Cotizar en S3; importar si es necesario desde China (3–4 sem) | Samuel |
| R8 | Motor de gasolina incompatible con alternador seleccionado | Baja | Alto | Verificar medidas de eje antes de comprar alternador | Santiago |
| R9 | Batería LiFePO4 de AliExpress no cumple especificaciones | Media | Medio | Comprar a proveedor con reseñas verificadas; tener plan B con batería de AGM | Samuel + Santiago |
| R10 | Retraso en impresión 3D (falla de impresora, material) | Media | Medio | Tener acceso a 2 impresoras; iniciar impresión desde S9 | Andrés |

---

## 5. PRESUPUESTO DETALLADO POR CATEGORÍA

### 5.1 Resumen por Categoría

| Categoría | Presupuesto Estimado COP | % del Total |
|-----------|------------------------|-------------|
| Sistema mecánico (chasis, ejes, transmisión, taller) | $1.950.000 | 32.6% |
| Sistema de descascarillado (rodillos, pulidora, ventilador) | $1.200.000 | 20.1% |
| Sistema eléctrico de potencia (alternador, batería, boost, etc.) | $535.000 | 8.9% |
| Sistema electrónico de control (MCU, sensores, interfaz, PCB) | $419.040 | 7.0% |
| Manufactura aditiva FDM (material + impresión) | $200.000 | 3.3% |
| Cableado, conectores, herrería general | $150.000 | 2.5% |
| Documentación, herramientas, consumibles | $100.000 | 1.7% |
| Contingencia (10% sobre presupuesto estimado) | $420.000 | 7.0% |
| **TOTAL ESTIMADO** | **~$4.974.040** | **83.2%** |
| **MARGEN DISPONIBLE** | **~$1.025.960** | **17.1%** |
| **PRESUPUESTO TOTAL** | **$7.000.000** | **100%** |

> **Nota**: Los precios del BOM detallado en `04_BOM/BOM_Descascaradora_v1.xlsx` suman ~$5.980.000 COP incluyendo los ítems por confirmar. El margen de ~$1.020.000 COP cubre imprevistos y la posible diferencia entre cotizaciones y precios reales de compra.

### 5.2 Control de Gasto Semanal

Ver `10_Gestion/CONTROL_PRESUPUESTO.md` para el registro actualizado de:
- Gastos realizados con soporte (factura/recibo)
- Compromisos de pago (órdenes de compra)
- Proyección vs. presupuesto disponible
- Alertas si el gasto supera el 80% del presupuesto antes de la semana 10

---

## 6. INDICADORES DE SEGUIMIENTO (KPIs)

| KPI | Meta | Frecuencia | Responsable |
|-----|------|-----------|-------------|
| % tareas EDT completadas vs. plan | ≥ 90% por semana | Semanal | Samuel |
| % presupuesto comprometido vs. disponible | ≤ 85% hasta S10 | Semanal | Samuel |
| N° de pedidos con retraso > 1 semana | 0 | Semanal | Samuel |
| N° de actas semanales firmadas y archivadas | 100% | Semanal | Todos |
| N° de bitácoras actualizadas | 6/6 (todas) | Semanal | Todos |
| % del firmware completado (módulos) | Según EDT | Quincenal | Samuel |
| N° de planos CAD exportados a repositorio | Según EDT | Quincenal | Nicolás |
| Eficiencia descascarillado medida | ≥ 85% | S13 (prueba) | Nicolás |
| Capacidad medida | ≥ 150 kg/h | S13 (prueba) | Todos |

---

*Gestión del Proyecto DAMSPI-150 v2.0 | Abril 2026 | PAI 2017275 — Grupo B*
*Responsable de gestión: Samuel D. Sánchez C.*
