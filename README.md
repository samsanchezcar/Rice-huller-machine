<div align="center">

# DAMSPI-150
## Descascaradora de Arroz Modular Semiautomática con Pesaje Integrado

**Proyecto Aplicado de Ingeniería — 2017275 | 1er Semestre 2026**
**Universidad Nacional de Colombia · Facultad de Ingeniería · Grupo B**

![Estado](https://img.shields.io/badge/Estado-En%20Diseño%20Detallado-yellow?style=for-the-badge)
![Fase](https://img.shields.io/badge/Fase%20Actual-Diseño%20Módulos-blue?style=for-the-badge)
![Presupuesto](https://img.shields.io/badge/Presupuesto-$7.000.000%20COP-green?style=for-the-badge)
![Capacidad](https://img.shields.io/badge/Capacidad-150%20kg%2Fh-orange?style=for-the-badge)

</div>

---

## Tabla de Contenido

1. [Resumen Ejecutivo](#1-resumen-ejecutivo)
2. [Equipo de Trabajo](#2-equipo-de-trabajo)
3. [Estructura del Repositorio](#3-estructura-del-repositorio)
4. [Arquitectura del Sistema](#4-arquitectura-del-sistema)
5. [Guía de Fase del Proyecto](#5-guía-de-fase-del-proyecto)
6. [Proveedores Clave](#6-proveedores-clave)
7. [Instrucciones de Uso](#7-instrucciones-de-uso)
8. [Estado de Componentes](#8-estado-de-componentes)
9. [Pendientes por Fase](#9-pendientes-por-fase)
10. [Normas y Convenciones del Repositorio](#10-normas-y-convenciones-del-repositorio)

---

## 1. Resumen Ejecutivo

El **DAMSPI-150** es un equipo semiautomático para el descascarillado de arroz paddy (*Oryza sativa*) diseñado para operar en campo, sin acceso a red eléctrica, con capacidad de **150 kg/h**. Surge de la necesidad de los pequeños y medianos productores de arroz de la región de Neiva (Huila) de reducir su dependencia de los molinos industriales y aumentar el valor agregado de su producto en origen.

El sistema está organizado en **4 módulos desmontables** con peso máximo de 25 kg cada uno, permitiendo su transporte y montaje por dos o tres personas sin herramientas especializadas. Incorpora un **sistema de control automático de pesaje** que detiene el proceso al alcanzar el peso de un bulto objetivo (10, 25 o 50 kg), accionando el embrague electromagnético y la compuerta de la tolva.

| Parámetro | Valor |
|-----------|-------|
| Nombre del sistema | DAMSPI-150 |
| Solicitante | Diego Alexander Castro Neira — Diego Castro Industria y Construcción S.A.S. |
| Capacidad objetivo | 150 kg/h de arroz paddy (humedad 18–22%) |
| Motor | Gasolina 6.5 HP / 3600 RPM (ya adquirido) |
| Módulos | 4 módulos desmontables (Potencia, Descascarillado, Control/Pesaje, Chasis) |
| Peso máx. por módulo | ≤ 25 kg |
| Presupuesto total | $7.000.000 COP (aportado por solicitante) |
| Presupuesto estimado | ~$5.980.000 COP (margen de ~$1.020.000) |
| Microcontrolador | PIC18F4550 |
| Interfaz de usuario | LCD 20×4 I2C + Teclado matricial 4×4 |
| Embrague | Electromagnético DC 24V — DLD6-05 tipo A |
| Eficiencia descascarillado | ≥ 85% en primera pasada |
| Precisión pesaje | ±100 g |
| Tiempo de ensamble | ≤ 60 minutos |
| Piezas estructurales | Manufactura aditiva FDM (PETG / PLA+) con optimización topológica previa |
| Semestre | 1er Semestre 2026 (14 semanas: 3 Feb – 30 May 2026) |

---

## 2. Equipo de Trabajo

| Nombre | Código | Área Principal | Responsabilidades Clave |
|--------|--------|---------------|------------------------|
| **Nicolás Herreño Fuentes** | — | Diseño Mecánico (Líder) | Cálculos de transmisión, memorias de cálculo, CAD Onshape, planos de fabricación |
| **Sebastián D. Millan B.** | — | Diseño Mecánico | Cálculos elementos de máquinas, CAD, diseño eje secundario |
| **Andrés G. Pinilla M.** | — | Manufactura y CAD | Talleres externos, Onshape, optimización topológica + FDM |
| **Samuel D. Sánchez C.** | — | Electrónica / Control / **Gestión** | Firmware PIC18F4550, sistema de pesaje, **gestión de proveedores, cotizaciones, BOM, compras**, finanzas |
| **Gabriel E. Bojacá M.** | — | Electrónica / Financiero | Circuito electrónico, PCB, interfaz LCD-teclado, gestión presupuesto |
| **Santiago Ávila C.** | — | Eléctrico / Potencia | Alternador, carga batería, cableado potencia, sistema eléctrico Módulo 1 |

> **Nota de gestión**: Samuel es el responsable único de toda la coordinación con proveedores: contacto inicial, solicitud de cotizaciones, seguimiento de pedidos, recepción de componentes y registro en el BOM. Toda compra debe quedar registrada antes de ejecutarse.

---

## 3. Estructura del Repositorio

```
DAMSPI-150/
│
├── README.md                          ← Este archivo — guía maestra del proyecto
│
├── 01_Informe/                        ← Informes de avance (Partes I, II y III)
│   ├── Informe_Avance_Parte_I_Descascaradora.docx   ← Entrega S4 (completada)
│   ├── Informe_Parte_II_Diseño_Detallado.docx        ← Entrega S8 (en progreso)
│   ├── Informe_Parte_III_Final.docx                  ← Entrega S14 (pendiente)
│   ├── boceto_arquitectura_modular.png
│   ├── sistema_potencia_electrica.svg
│   └── Diagramas_bloques.pdf
│
├── 02_Actas/                          ← Actas semanales y documentos legales
│   ├── Acuerdo_Solicitante.pdf        ← AS firmado
│   ├── contrato_social.pdf            ← CS firmado
│   ├── Acta_S01.pdf
│   ├── Acta_S02.pdf
│   ├── Acta_S03.pdf
│   └── Acta_SColchon.pdf
│
├── 03_Cronograma_GANTT/               ← Planificación y seguimiento
│   ├── GANTT_Descascaradora_v2.xlsx   ← GANTT original (referencia)
│   └── GANTT-PAI1B.pdf
│
├── 04_BOM/                            ← Lista de materiales
│   └── BOM_Descascaradora_v1.xlsx     ← BOM con 34 ítems (~$5.98M COP)
│
├── 05_CAD_Planos/                     ← Modelos 3D y planos de fabricación
│   ├── Onshape_Link.md                ← Enlace al modelo Onshape compartido
│   └── (exportar aquí planos PDF/DWG al finalizar cada módulo)
│
├── 06_Estado_del_Arte_Referencias/    ← Literatura técnica y normativa
│   ├── Baker_Tribologia_Molineria_Arroz.pdf
│   ├── Design_Fabrication_Rice_Hulling.pdf
│   ├── Manual_Tecnico_Descascaradora_Referencia.pdf
│   ├── Referencia_Adicional_Procesamiento_Arroz.pdf
│   └── rm05.pdf
│
├── 07_Bitacoras/                      ← Bitácoras semanales individuales
│   ├── Bitacora_Nicolas.md
│   ├── Bitacora_Sebastian.md
│   ├── Bitacora_Andres.md
│   ├── Bitacora_Samuel.md
│   ├── Bitacora_Gabriel.md
│   └── Bitacora_Santiago.md
│
├── 08_Electronica/                    ← Todo lo electrónico (MCU, sensores, firmware)
│   ├── GUIA_ELECTRONICA.md            ← Guía técnica electrónica completa ★
│   ├── firmware/                      ← Código fuente PIC18F4550
│   │   ├── DAMSPI150.X/              ← Proyecto MPLAB X
│   │   └── LibLCD_I2C_XC8.h         ← Librería LCD I2C para XC8
│   └── esquematicos/                  ← Esquemáticos del circuito de control
│
├── 09_Electrica/                      ← Todo lo eléctrico (potencia, alternador, batería)
│   ├── GUIA_ELECTRICA.md             ← Guía técnica eléctrica-potencia completa ★
│   └── diagramas/                     ← Diagramas del sistema de potencia eléctrica
│
└── 10_Gestion/                        ← Gestión del proyecto
    ├── GESTION_PROYECTO.md            ← EDT detallado + Gantt + gestión compras ★
    ├── REGISTRO_PROVEEDORES.md        ← Contactos, cotizaciones y seguimiento (Samuel)
    └── CONTROL_PRESUPUESTO.md        ← Control de gastos vs. presupuesto
```

> Los archivos marcados con **★** son documentos técnicos vivos que deben actualizarse semanalmente.

---

## 4. Arquitectura del Sistema

El DAMSPI-150 se organiza en cuatro módulos funcionales independientes:

```
┌─────────────────────────────────────────────────────────────────────┐
│                    DAMSPI-150 — VISTA FUNCIONAL                     │
├──────────────┬──────────────────┬──────────────────┬───────────────┤
│  MÓDULO 1    │    MÓDULO 2      │    MÓDULO 3       │  MÓDULO 4     │
│  POTENCIA    │  DESCASCARILLADO │  CONTROL/PESAJE   │  CHASIS       │
│              │                  │                   │               │
│ Motor 6.5HP  │  Rodillos PU     │  PIC18F4550       │  Estructura   │
│ Alternador   │  Ø80mm / 200mm   │  LCD 20×4 I2C     │  acero 40×40  │
│ Batería 24V  │  Ventilador      │  Teclado 4×4      │  Chasis       │
│ Embrague     │  centrífugo      │  HX711 + 4 celdas │  soldado      │
│ Boost 14→24V │  Sin Fín alim.   │  SSR + Embrague   │  Ruedas       │
│ Buck 24→5V   │  Pulidora horiz. │  Servo tolva      │  Pasadores    │
│              │  (opcional)      │  Pilotos / Buzzer │  conex. rápida│
│  ~22 kg      │  ~18 kg          │  ~8 kg            │  ~15 kg       │
└──────────────┴──────────────────┴──────────────────┴───────────────┘
       │                │                  │                │
       └────────────────┴──────────────────┴────────────────┘
                    Correas en V / Poleas / Ejes de transmisión
```

**Documentación técnica por área:**

| Área | Documento | Responsable |
|------|-----------|-------------|
| Sistema electrónico (MCU, firmware, sensores, interfaz) | [`08_Electronica/GUIA_ELECTRONICA.md`](08_Electronica/GUIA_ELECTRONICA.md) | Samuel, Gabriel |
| Sistema eléctrico (potencia, alternador, batería, carga) | [`09_Electrica/GUIA_ELECTRICA.md`](09_Electrica/GUIA_ELECTRICA.md) | Santiago, Samuel |
| Gestión, EDT, Gantt, proveedores, compras | [`10_Gestion/GESTION_PROYECTO.md`](10_Gestion/GESTION_PROYECTO.md) | Samuel |

---

## 5. Guía de Fase del Proyecto

### Semana Actual → Ver `10_Gestion/GESTION_PROYECTO.md` para detalle completo

| Fase | Semanas | Estado | Entregable |
|------|---------|--------|------------|
| **F1** — Formulación y requisitos | S1–S3 | ✅ Completada | Informe Parte I |
| **F2** — Diseño Módulo Potencia | S3–S6 | 🔄 En progreso | Memorias cálculo + CAD |
| **F3** — Diseño Electrónico y Control | S4–S7 | 🔄 En progreso | Circuito + Firmware |
| **F4** — Diseño Módulo Descascarillado | S3–S8 | 🔄 En progreso | Informe Parte II |
| **F4G** — Gestión proveedores y compras | S3–S10 | 🔄 En progreso | Registro Proveedores |
| **F5** — Manufactura y montaje | S8–S12 | ⏳ Pendiente | Prototipo ensamblado |
| **F6** — Validación y pruebas | S12–S13 | ⏳ Pendiente | Video + resultados |
| **F7** — Documentación y entrega | S13–S14 | ⏳ Pendiente | Informe Parte III |

### Checklist de la Semana en Curso

Antes de cada reunión semanal, verificar:

- [ ] Acta de la semana anterior firmada y archivada en `02_Actas/`
- [ ] Bitácoras individuales actualizadas en `07_Bitacoras/`
- [ ] BOM actualizado con nuevas adquisiciones o cotizaciones (`04_BOM/`)
- [ ] Samuel: actualizar `10_Gestion/REGISTRO_PROVEEDORES.md` con estado de pedidos
- [ ] Avance de CAD subido a Onshape (link en `05_CAD_Planos/Onshape_Link.md`)
- [ ] Samuel/Gabriel: commits de firmware en `08_Electronica/firmware/`
- [ ] GANTT actualizado con estado real de avance

---

## 6. Proveedores Clave

| Proveedor | Productos | Contacto | Responsable |
|-----------|-----------|----------|-------------|
| **Solagro Colombia** | Rodillos PU Ø80mm, pulidora horizontal, repuestos | solagro.co/repuestos | Samuel |
| **MercadoLibre Colombia** | Embrague DLD6-05, SSR, electrónica general | mercadolibre.com.co | Samuel |
| **AliExpress** | Celdas de carga tipo S, PIC18F4550, batería LiFePO4, LCD 20×4, teclado 4×4 | aliexpress.com | Samuel |
| **Homecenter** | Motor 6.5HP (ya adquirido) | homecenter.com.co | — |
| **Ferreterías industriales Bogotá** | Perfiles acero, tornillería, rodamientos, poleas | Local Bogotá | Gabriel / Samuel |
| **Taller externo UNAL** | Mecanizado ejes, soldadura chasis | Campus UNAL | Nicolás, Andrés |
| **Naylampmechatronics** | HX711, electrónica | naylampmechatronics.com | Samuel |
| **Siesa Industrial** | E-Stop, pilotos LED industriales | Local Bogotá | Samuel |

> **Ver detalle completo de cotizaciones y contactos en:** [`10_Gestion/REGISTRO_PROVEEDORES.md`](10_Gestion/REGISTRO_PROVEEDORES.md)

---

## 7. Instrucciones de Uso

### Informe Principal
1. Abrir `01_Informe/Informe_Avance_Parte_*.docx` en Word/Google Docs
2. Actualizar tabla de contenido: **Referencias → Actualizar tabla → Todo el documento**
3. No modificar estructura de secciones sin actualizar el TOC

### BOM
- Abrir `04_BOM/BOM_Descascaradora_v1.xlsx`
- Totales calculados automáticamente (columna H = E × G)
- **Columna Estado**: `ADQUIRIDO` / `COTIZADO` / `Por adquirir` / `Por adquirir (Solagro)`
- Actualizar inmediatamente al recibir cualquier componente o cotización
- Samuel notifica al grupo cada actualización

### GANTT
- Abrir `03_Cronograma_GANTT/GANTT_Descascaradora_v2.xlsx`
- Actualizar al inicio de cada semana con estado real
- EDT completo y mejorado en `10_Gestion/GESTION_PROYECTO.md`

### Firmware (Electrónica)
- Abrir `08_Electronica/firmware/DAMSPI150.X/` con **MPLAB X IDE ≥ 6.0**
- Compilador: **XC8 ≥ 3.0**
- Programador: **PICkit 3 o PICkit 4** (ICSP)
- Ver documentación completa en `08_Electronica/GUIA_ELECTRONICA.md`

### CAD (Onshape)
- Link al modelo compartido en `05_CAD_Planos/Onshape_Link.md`
- Exportar planos PDF/DWG a `05_CAD_Planos/` al completar cada módulo
- Usar prefijo de versión: `v1.0_`, `v1.1_`, etc.

---

## 8. Estado de Componentes

| N° | Componente | Módulo | Precio Unit. | Estado | Resp. |
|----|-----------|--------|-------------|--------|-------|
| 1 | Motor gasolina 6.5HP | Mod.1 | $750.000 | ✅ ADQUIRIDO | — |
| 2 | Embrague DLD6-05 24V | Mod.1 | $300.000 | 📋 COTIZADO | Samuel |
| 3 | Celda de carga tipo S 10kg ×4 | Mod.3 | $57.045 c/u | 📋 COTIZADO | Samuel |
| 4 | PIC18F4550 DIP-40 | Mod.3 | $31.018 | 📋 COTIZADO | Samuel |
| 5 | Batería LiFePO4 24V/5Ah | Mod.1 | $250.000 | 📋 COTIZADO | Santiago |
| 6 | HX711 ADC 24 bits | Mod.3 | $15.000 | 🛒 Por adquirir | Samuel |
| 7 | LCD 20×4 + módulo I2C | Mod.3 | $25.000 | 🛒 Por adquirir | Samuel |
| 8 | Teclado matricial 4×4 | Mod.3 | $15.000 | 🛒 Por adquirir | Samuel |
| 9 | Rodillos PU Ø80mm (par) | Mod.2 | $400.000 | 🔍 Solagro | Samuel |
| 10 | Pulidora horizontal | Mod.2 | $600.000 | 🔍 Solagro | Samuel |
| 11 | Alternador motocicleta | Mod.1 | $180.000 | 🛒 Por adquirir | Santiago |
| … | *(ver BOM completo)* | — | — | — | — |

> Leyenda: ✅ Adquirido | 📋 Cotizado | 🛒 Por adquirir | 🔍 En gestión con proveedor específico

---

## 9. Pendientes por Fase

### Fase Actual (S4–S7) — Diseño Detallado

**Mecánica (Nicolás, Sebastián, Andrés):**
- [ ] Memorias de cálculo: eje secundario, transmisión por poleas
- [ ] Diseño CAD Módulo 2: rodillos, ajustador, ventilador, Sin Fín
- [ ] Diseño CAD Módulo 4: chasis, puntos de conexión rápida
- [ ] Optimización topológica de piezas para FDM (Andrés)
- [ ] Contacto con taller externo para mecanizado de ejes

**Electrónica (Samuel, Gabriel):**
- [ ] Diseño esquemático PCB del circuito de control (Módulo 3)
- [ ] Iniciar firmware: `initPorts()`, `initLCD_I2C()`, `hx711_init()`
- [ ] Selección y pedido: LCD 20×4, teclado 4×4, HX711, SSR

**Eléctrica (Santiago, Samuel):**
- [ ] Diseño detallado: alternador → rectificador → boost → batería
- [ ] Cotización del Boost DC-DC 14V→24V 5A
- [ ] Diseño de canaletas y cableado entre módulos

**Gestión (Samuel):**
- [ ] Contactar Solagro para rodillos y pulidora (cotización formal)
- [ ] Confirmar pedido AliExpress: celdas de carga, PIC, batería
- [ ] Actualizar REGISTRO_PROVEEDORES.md con tiempos de entrega

### Siguiente Entrega (Parte II — Semana 8)
- [ ] Diseño conceptual con bocetos de todos los módulos
- [ ] Diagramas de caja negra y caja gris
- [ ] Memorias de cálculo completas (transmisión, rodillos, ejes)
- [ ] Modelos CAD 3D avanzados en Onshape
- [ ] Planos preliminares de fabricación
- [ ] Cronograma definitivo actualizado

---

## 10. Normas y Convenciones del Repositorio

### Nomenclatura de Archivos
```
[Módulo]_[Descripción]_v[X.Y].[ext]
Ejemplos:
  Mod3_Esquematico_Control_v1.0.pdf
  Mod1_CAD_BaseMotor_v2.1.step
  Acta_S05_20260310.pdf
```

### Versionado de Documentos
- `v1.0` → Primera versión entregable
- `v1.X` → Correcciones menores (sin cambio de estructura)
- `v2.0` → Revisión mayor (cambio de diseño o nueva fase)

### Convenciones de Código (Firmware)
- Comentarios en español
- Funciones: `camelCase` (ej. `realizarTara()`)
- Constantes: `MAYUSCULAS_CON_GUION` (ej. `PESO_OBJETIVO_KG`)
- Un archivo por módulo funcional (ver `08_Electronica/GUIA_ELECTRONICA.md`)

### Actualización del BOM
- Toda compra, cotización o cambio de precio debe registrarse el mismo día
- Samuel envía resumen semanal al grupo por WhatsApp/Discord
- Los precios en el BOM son precios de compra real (no estimados)

---

## Información del Solicitante

| Campo | Valor |
|-------|-------|
| Nombre | Diego Alexander Castro Neira |
| Empresa | Diego Castro Industria y Construcción S.A.S. |
| NIT | 9009608102 |
| Correo | dicaindustria@gmail.com |
| Teléfono | 315-255-2560 |
| Ubicación de entrega | Neiva, Huila, Colombia |

---

*Versión: 2.0 | Última actualización: Abril 2026 | Equipo Grupo B — PAI 2017275*
