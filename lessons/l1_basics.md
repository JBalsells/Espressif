# Proyecto con Espressif (ESP32 / ESP8266)

Este proyecto está diseñado para desarrollar y cargar firmware en microcontroladores **ESP32** o **ESP8266** utilizando **PlatformIO** o **ESP-IDF**.

---

## ¿Qué es un ESP32?

El **ESP32** es un microcontrolador de bajo costo y alto rendimiento desarrollado por **Espressif Systems**, ampliamente utilizado en proyectos de electrónica, domótica e Internet de las Cosas (IoT). Es el sucesor del popular **ESP8266**, pero con muchas más funcionalidades y mejor rendimiento.

### Características principales

- **Arquitectura:** Procesador Xtensa® LX6 de 32 bits (doble o núcleo único según el modelo).
- **Velocidad:** Hasta 240 MHz de frecuencia de reloj.
- **Memoria:** SRAM interna de hasta 520 KB.
- **Flash:** Memoria externa comúnmente de 4 MB (según el módulo).
- **Conectividad:**
  - Wi-Fi 802.11 b/g/n
  - Bluetooth 4.2 y Bluetooth Low Energy (BLE)
- **GPIO:** Hasta 34 pines programables.
- **Periféricos:** Soporte para PWM, ADC, DAC, SPI, I2C, UART, I2S, etc.
- **Sensores integrados:** Sensor Hall y sensores táctiles capacitivos.
- **Modos de bajo consumo:** Deep Sleep, Light Sleep (ideales para proyectos con batería).

---

## Instalación de PlatformIO

1. Instala [Visual Studio Code](https://code.visualstudio.com/)
2. Abre VS Code y dirígete a la sección de extensiones.
3. Busca e instala **PlatformIO IDE**.

### Instalación de Visual Studio Code y PlatformIO

#### 1. Instalar Visual Studio Code

- Descargar desde el sitio oficial: [https://code.visualstudio.com/](https://code.visualstudio.com/)
- Disponible para **Windows**, **macOS** y **Linux**.
- Instalar como cualquier otra aplicación.

#### 2. Instalar PlatformIO en Visual Studio Code

1. Abrir Visual Studio Code.
2. Ir a la pestaña de **Extensiones** (icono de cuadrados en la barra lateral izquierda o presionar `Ctrl+Shift+X`).
3. Buscar `PlatformIO IDE`.
4. Hacer clic en **Instalar**.
5. Esperar unos minutos mientras se descargan las dependencias necesarias (Python, toolchains, etc.).

#### 3. Verificar instalación

- Una vez instalado, aparecerá un ícono de PlatformIO (una hormiga) en la barra lateral izquierda.
- Desde ahí puedes crear nuevos proyectos, importar ejemplos y configurar placas Espressif como ESP32 o ESP8266.

---

## Crear un nuevo proyecto en PlatformIO

1. Abre PlatformIO desde la barra lateral (ícono de hormiga).
2. Haz clic en **New Project**.
3. Completa los siguientes campos:
   - **Project name:** `mi_proyecto_esp32`
   - **Board:** `ESP32 Dev Module` (u otra compatible)
   - **Framework:** `Arduino` o `ESP-IDF`
   - **Location:** Carpeta destino del proyecto
4. Haz clic en **Finish**.

PlatformIO generará automáticamente la estructura del proyecto.

---

## Estructura del Proyecto

```plaintext
.
├── include/             # Archivos de cabecera (.h)
├── lib/                 # Librerías externas o propias
├── src/                 # Código fuente principal
│   └── main.cpp         # Punto de entrada
├── test/                # Pruebas unitarias
├── platformio.ini       # Configuración del entorno
└── README.md            # Documentación del proyecto
```

### Descripción los directorios y archivos más importantes del proyecto:

### `include/`  
Contiene los **archivos de cabecera** (`.h`) del proyecto. Aquí se definen prototipos de funciones, constantes, macros y estructuras utilizadas en el código fuente.  
Ideal para mantener una separación clara entre la declaración y la implementación.

### `lib/`  
Directorio para incluir **librerías externas** o librerías propias reutilizables.  
Cada subdirectorio dentro de `lib/` puede contener su propio conjunto de archivos fuente (`.cpp`) y cabecera (`.h`).

### `src/`  
Contiene el **código fuente principal** del proyecto. Este es el corazón de tu aplicación, donde implementas la lógica del programa.  
Por convención, PlatformIO busca un archivo llamado `main.cpp` o `main.c` como punto de entrada.

#### `src/main.cpp`  
Este archivo contiene el **punto de entrada del programa** y es uno de los archivos más importantes del proyecto.

Si estás usando el framework **Arduino**:

`main.cpp` debe implementar las funciones especiales `setup()` y `loop()`:

- `setup()` se ejecuta una sola vez al inicio, y sirve para configurar pines, inicializar periféricos, establecer conexiones, etc.
- `loop()` se ejecuta de forma continua después de `setup()`, y representa el ciclo principal del programa (por ejemplo, leer sensores, enviar datos, etc.).

uando se usa el framework espidf (Espressif IoT Development Framework), el archivo main.cpp o main.c debe contener una función llamada app_main(), que es el punto de entrada del sistema bajo FreeRTOS, el sistema operativo embebido usado por ESP-IDF.

En lugar de setup() y loop(), defines directamente la lógica en app_main() y, si es necesario, puedes crear tareas (xTaskCreate) para ejecutar funciones en paralelo.

### `test/`  
Aquí se ubican los **tests unitarios** del proyecto. Puedes usar frameworks como Unity (integrado en PlatformIO) para hacer pruebas automáticas del código.

### `platformio.ini`  
Archivo de **configuración del entorno PlatformIO**. Aquí defines la plataforma (por ejemplo, `espressif32`), la placa (`board`), el framework (`arduino`, `espidf`, etc.), la velocidad del monitor serie, y otros parámetros del entorno.

---

## Configuración (`platformio.ini`)

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

### Configuración de PlatformIO para ESP32 con ESP-IDF en `platformio.ini`

Este bloque define la configuración necesaria para compilar, cargar y depurar un proyecto con ESP32 usando el framework **ESP-IDF**.

1. **`[env:esp32dev]`**  
   Define un **entorno de compilación** llamado `esp32dev`.  
   PlatformIO permite tener múltiples entornos para diferentes placas o configuraciones.  
   Este nombre se usa internamente para compilar o subir código bajo ese entorno.

2. **`platform = espressif32`**  
   Especifica la **plataforma de hardware** a utilizar.  
   `espressif32` incluye soporte para toda la familia ESP32:  
   - ESP32-WROOM  
   - ESP32-S2/S3  
   - ESP32-C3, etc.

3. **`board = esp32dev`**  
   Define el **modelo de placa** compatible.  
   `esp32dev` es una configuración genérica válida para la mayoría de placas ESP32 DevKit.  
   Puedes explorar más placas aquí:  
   https://platformio.org/boards?platform=espressif32

4. **`framework = espidf`**  
   Especifica que se usará el framework **ESP-IDF** (Espressif IoT Development Framework).  
   - Es el framework oficial de bajo nivel para ESP32.  
   - Proporciona acceso directo al hardware.  
   - Integra el sistema operativo **FreeRTOS**.

5. **`upload_port = /dev/ttyUSB1`**  
   Define el **puerto serie** donde está conectado el ESP32.  
   Esto evita que PlatformIO lo detecte automáticamente.  
   - En Linux, suele ser `/dev/ttyUSB0`, `/dev/ttyUSB1`, etc.  
   - Puedes verificarlo con el comando:  
     ```bash
     ls /dev/ttyUSB*
     ```



## Dependencias

- [PlatformIO](https://platformio.org/) o [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/)
- Drivers USB para ESP32 / ESP8266
- Visual Studio Code (opcional, recomendado)
