
#include "sensor_temperatura.h"
#include <stdio.h>

float adc_sensor_de_temp;

void sensorTemperaturaIniciarCaptura(void); //metodos privados para que no se vean en la libreria principal
void sensorTemperaturaEsperarResultado(void);

void sensorTemperaturaIniciarCaptura(void){
	ADC16_SetChannelConfig(SENSOR_TEMPERATURA_ADC16_BASE, SENSOR_TEMPERATURA_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[0]);
}

void sensorTemperaturaEsperarResultado(void){

	while (0U == (kADC16_ChannelConversionDoneFlag
			& ADC16_GetChannelStatusFlags(SENSOR_TEMPERATURA_ADC16_BASE, SENSOR_TEMPERATURA_ADC16_CHANNEL_GROUP))){
	       }

}

float sensorTemperaturaObtenerDatoCelsius(void){
	sensorTemperaturaIniciarCaptura();
	sensorTemperaturaEsperarResultado();
	uint32_t resultadoADC;
	float volADC;
	resultadoADC = ADC16_GetChannelConversionValue(SENSOR_TEMPERATURA_ADC16_BASE, SENSOR_TEMPERATURA_ADC16_CHANNEL_GROUP);
	volADC=(3.3*resultadoADC)/40.95;

	return (volADC);
}

void sensorTe_ini (void){

}

void Sensortemp_Task_Run(void){
	adc_sensor_de_temp=sensorTemperaturaObtenerDatoCelsius();
}
