# Guía de Aprendizaje: ESP32

## 1. Fundamentos básicos

- **¿Qué es el ESP32?**
    - Microcontrolador de doble núcleo de 32 bits.
    - Soporta WiFi y Bluetooth.
    - Usado en proyectos de IoT, automatización, sensores, etc.

- **Instalación y uso del entorno de desarrollo**
    - Visual Studio Code + PlatformIO o Arduino IDE.
    - Instalación de drivers USB para el ESP32.
    - Selección del modelo (ej: ESP32 Dev Module, ESP32 WROOM32).

    - Subir código al ESP32.
    - Configurar puerto serie y velocidad de transmisión.

---

## 2. Primeros programas

- **Hola mundo:** Generador de onda cuadrada (Blink / Parpadeo de LED).
- **Uso de GPIOs**
- **Entradas y salidas digitales**

---

## 3. ADC/DAC
- **Convertidor análogo digital**
- **Convertidor digital análogo**
---

## 4. PWM
- **Modulación por ancho de pulso**

---

## 5. Comunicación

- **Comunicación serial**
    - Uso del monitor serial
    - Comunicación con otros dispositivos vía UART.

- **I2C y SPI**
    - Protocolos para sensores y pantallas.
    - Librerías comunes:
    - `Wire.h` (I2C)
    - `SPI.h`
    - I2C maestro/esclavo entre microcontroladores.
- **Comunicación inalámbrica (WiFi/Bluetooth)**
    - Conexión a red local.
    - Peticiones HTTP.
    - Envío de datos por Bluetooth

---

## 6. Sensores

- DHT11 / DHT22 (temperatura y humedad).
- MPU6050 (acelerómetro y giroscopio).
- Otros sensores:
  - TCS34725 (color)
  - BH1750 (intensidad de luz)

---

## 7. Actuadores

- Relés
- Motores:
  - Motores DC
  - Servomotores
  - Motores paso a paso
  - Motores trifásicos
- Pantallas:
  - OLED
  - TFT

---

## 8. Temas avanzados
-   **Interrupciones**
-   **Temporizadores**

---

## 9. Temas avanzados
-   **Deep Sleep y ahorro de energía**
    - Modos de bajo consumo.
-   **OTA (Over-The-Air)**
    - Actualización remota del firmware.
-   **RTOS (ESP-IDF)**
    - Multitarea con FreeRTOS.
    - Tareas
    - Colas

---

## 10. Proyectos IoT

- Envío de datos a la nube usando:
  - HTTP
  - MQTT
  - WebSocket
- Plataformas comunes:
  - ThingSpeak
  - Blynk
  - Firebase
  - Node-RED