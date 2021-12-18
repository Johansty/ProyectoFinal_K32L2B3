

#ifndef IOT_SDK_PERIPHERALS_SENSOR_LUMINOSIDAD_H_
#define IOT_SDK_PERIPHERALS_SENSOR_LUMINOSIDAD_H_


#include "peripherals.h"

#define SENSOR_LUMINOSIDAD_ADC16_BASE          ADC0
#define SENSOR_LUMINOSIDAD_ADC16_CHANNEL_GROUP 0
#define DEMO_ADC16_USER_CHANNEL2  12U /* PTB2, ADC0_SE12 */

float sensorLuminosidadObtenerDato(void);

// parte modulo

void sensorLum_ini(void);
void Sensorlum_Task_Run(void);



#endif /* IOT_SDK_PERIPHERALS_SENSOR_LUMINOSIDAD_H_ */
