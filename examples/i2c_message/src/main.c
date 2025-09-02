#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"

#define I2C_MASTER_NUM         I2C_NUM_0
#define I2C_MASTER_SDA_IO      21
#define I2C_MASTER_SCL_IO      22
#define I2C_MASTER_FREQ_HZ     100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

#define SLAVE_ADDR             0x3C  // Cualquier dirección válida (7 bits)

void i2c_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode,
                       I2C_MASTER_RX_BUF_DISABLE,
                       I2C_MASTER_TX_BUF_DISABLE, 0);
}

void send_i2c_message_for_analysis(const char* message)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (SLAVE_ADDR << 1) | I2C_MASTER_WRITE, false);  // ignora ACK
    i2c_master_write(cmd, (uint8_t*)message, strlen(message), false);         // ignora ACK
    i2c_master_stop(cmd);

    // Ejecuta el comando sin importar si hay ACK
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);
}

void app_main(void)
{
    i2c_master_init();

    const char* message = "HOLA MUNDO esta es una prueba de hardware";

    while (1) {
        send_i2c_message_for_analysis(message);
        vTaskDelay(pdMS_TO_TICKS(2000));  // espera 2s entre mensajes
    }
}

