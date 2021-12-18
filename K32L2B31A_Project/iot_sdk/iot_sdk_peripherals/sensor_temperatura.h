
#ifndef IOT_SDK_PERIPHERALS_SENSOR_TEMPERATURA_H_
#define IOT_SDK_PERIPHERALS_SENSOR_TEMPERATURA_H_

#include "peripherals.h"

#define SENSOR_TEMPERATURA_ADC16_BASE          ADC0
#define SENSOR_TEMPERATURA_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL  8U /* PTB0, ADC0_SE8 */

float sensorTemperaturaObtenerDatoCelsius(void);

// parte modulo
void sensorTe_ini(void);
void Sensortemp_Task_Run(void);
#endif /* IOT_SDK_PERIPHERALS_SENSOR_TEMPERATURA_H_ */
