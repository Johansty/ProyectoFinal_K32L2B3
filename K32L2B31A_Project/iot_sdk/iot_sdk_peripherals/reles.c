

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO_IN1    BOARD_SW1_GPIO
#define BOARD_LED_GPIO_PIN_IN1 12U
#define BOARD_LED_GPIO_IN2    BOARD_SW1_GPIO
#define BOARD_LED_GPIO_PIN_IN2 13U
/*******************************************************************************/

void Reles_ini(){
gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

GPIO_PinInit(BOARD_LED_GPIO_IN1, BOARD_LED_GPIO_PIN_IN1, &led_config);
GPIO_PinInit(BOARD_LED_GPIO_IN2, BOARD_LED_GPIO_PIN_IN2, &led_config);

}

void encender_rele_IN1(){
	GPIO_PortClear(BOARD_LED_GPIO_IN1, 1u << BOARD_LED_GPIO_PIN_IN1);
}

void apagar_rele_IN1(){
	GPIO_PortSet(BOARD_LED_GPIO_IN1, 1u << BOARD_LED_GPIO_PIN_IN1);
}

void encender_rele_IN2(){
	GPIO_PortClear(BOARD_LED_GPIO_IN2, 1u << BOARD_LED_GPIO_PIN_IN2);
}

void apagar_rele_IN2(){
	GPIO_PortSet(BOARD_LED_GPIO_IN2, 1u << BOARD_LED_GPIO_PIN_IN2);
}

