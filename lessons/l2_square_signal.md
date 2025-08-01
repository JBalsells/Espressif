# Explicación paso a paso: Parpadeo de LED con ESP32 usando ESP-IDF

Este archivo describe detalladamente el funcionamiento de un programa que parpadea un LED utilizando el framework **ESP-IDF** de Espressif. El programa configura un pin GPIO como salida, y enciende y apaga un LED en intervalos definidos usando funciones de FreeRTOS. El lenguaje principal que se utiliza en ESP-IDF (Espressif IoT Development Framework) es C, aunque también puedes usar C++ si se configura adecuadamente.

---

## Partes principales de un programa en C
1. **Directivas de Preprocesador** 
Se colocan al inicio del archivo y se usan para:
- Incluir bibliotecas estándar o propias (`#include`)
- Definir constantes (`#define`)
    ```c
    #include <stdio.h>       // Biblioteca estándar de entrada/salida
    #define PI 3.14159       // Constante simbólica
    ```

2. **Declaraciones Globales**
Variables y prototipos de funciones que estarán disponibles en todo el archivo.
    ```c
    int sumar(int a, int b);      // Prototipo de función
    int contador_global = 0;      // Variable global
    ```
3. **Función Principal**
Es el punto de entrada del programa. Aquí comienza la ejecución del código.
    ```c
    int main(void) {
        int resultado = sumar(5, 3);      // Llamada a función
        printf("Resultado: %d\n", resultado);
        return 0;                         // Fin del programa
    }
    ```

4. **Funciones Auxiliares**
Sirven para organizar el código y evitar la repetición. Se pueden definir después de main().
    ```c
    int sumar(int a, int b) {
        return a + b;
    }
    ```

5. **Comentarios**
No afectan la ejecución del programa, pero ayudan a entender el código.
    ```c
    // Comentario de una línea

    /*
    Comentario
    de varias líneas
    */
    ```

---

## Código para generación de una onda cuadrada

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO GPIO_NUM_2  // ¡Cambiar a un pin válido como 2, 5, etc!

void app_main(void)
{
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(10));

        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
```


## Análisis detallado del código (paso a paso)

1. **`#include <stdio.h>`**  
   Importa la biblioteca estándar de C que permite utilizar funciones como `printf()`.  
   Aunque no se utiliza directamente en este ejemplo, es útil para depuración.

2. **`#include "freertos/FreeRTOS.h"`**  
   Incluye las definiciones básicas del sistema operativo FreeRTOS, el núcleo multitarea que utiliza ESP-IDF.

3. **`#include "freertos/task.h"`**  
   Proporciona funciones para trabajar con tareas (threads) en FreeRTOS.  
   Se utiliza aquí para la función `vTaskDelay()`, que implementa pausas sin bloquear el sistema.

4. **`#include "driver/gpio.h"`**  
   Incluye las funciones necesarias para controlar los pines GPIO del ESP32.  
   Permite configurar pines como entrada/salida y cambiar su estado lógico.

5. **`#define BLINK_GPIO GPIO_NUM_2`**  
   Define una constante llamada `BLINK_GPIO` que representa el pin GPIO número 2 del ESP32.  
   Este valor puede cambiarse fácilmente si se desea utilizar otro pin.

6. **`void app_main(void)`**  
   Esta es la función principal del programa.  
   En ESP-IDF, reemplaza a `main()` en C tradicional y se ejecuta al finalizar la inicialización del sistema.

7. **`gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);`**  
   Configura el pin especificado (`BLINK_GPIO`) como una salida digital.  
   Esto permite enviar señales desde el ESP32 hacia otros componentes (como un LED).

8. **`while (1)`**  
   Inicia un bucle infinito. En sistemas embebidos, esto es común para ejecutar una lógica continua.

9. **`gpio_set_level(BLINK_GPIO, 1);`**  
   Establece el pin en **nivel alto** (3.3V), lo que enciende el LED.

10. **`vTaskDelay(pdMS_TO_TICKS(10));`**  
    Pausa la tarea actual durante 10 milisegundos sin bloquear el resto del sistema.  
    - `vTaskDelay()` es una función de FreeRTOS para retardos no bloqueantes.  
    - `pdMS_TO_TICKS()` convierte milisegundos a "ticks" del sistema.

11. **`gpio_set_level(BLINK_GPIO, 0);`**  
    Establece el pin en **nivel bajo** (0V), apagando el LED.

12. **`vTaskDelay(pdMS_TO_TICKS(100));`**  
    Espera 100 milisegundos antes de repetir el ciclo, generando así el parpadeo visible.

---



## Visualización en Analizador Lógico
![ESP32](../documents/lessons_images/l2_2.png)

Si cambiamos uno de los tiempos que aparecen en el código, específicamente los 10 ms por 100 ms, tendríamos una señal de la siguiente manera:

![ESP32](../documents/lessons_images/l2_1.png)