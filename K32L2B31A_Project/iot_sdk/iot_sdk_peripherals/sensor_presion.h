
#ifndef IOT_SDK_PERIPHERALS_SENSOR_PRESION_H_
#define IOT_SDK_PERIPHERALS_SENSOR_PRESION_H_

#include "peripherals.h"

#define SENSOR_PRESION_ADC16_BASE          ADC0
#define SENSOR_PRESION_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL1  12U /* PTB3, ADC0_SE13 */

float sensorPresionObtenerDato(void);

// parte modulo

void sensorPe_ini(void);
void Sensorpres_Task_Run(void);

#endif /* IOT_SDK_PERIPHERALS_SENSOR_PRESION_H_ */
