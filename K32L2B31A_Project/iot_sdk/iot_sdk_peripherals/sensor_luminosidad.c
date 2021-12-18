
#include "sensor_luminosidad.h"
#include "math.h"
#include <stdio.h>

float adc_sensor_de_lum;

void sensorLuminosidadIniciarCaptura(void); //metodos privados para que no se vean en la libreria principal
void sensorLuminosidadEsperarResultado(void);

void sensorLuminosidadIniciarCaptura(void){
	ADC16_SetChannelConfig(SENSOR_LUMINOSIDAD_ADC16_BASE, SENSOR_LUMINOSIDAD_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[2]);
}

void sensorLuminosidadEsperarResultado(void){
	while (0U == (kADC16_ChannelConversionDoneFlag
			& ADC16_GetChannelStatusFlags(SENSOR_LUMINOSIDAD_ADC16_BASE, SENSOR_LUMINOSIDAD_ADC16_CHANNEL_GROUP))){
	       }

}
float sensorLuminosidadObtenerDato(void){
	sensorLuminosidadIniciarCaptura();
	sensorLuminosidadEsperarResultado();
	uint32_t resultadoADC;
	float lumADC, value1;
	float vref = 4.9;
	resultadoADC = ADC16_GetChannelConversionValue(SENSOR_LUMINOSIDAD_ADC16_BASE, SENSOR_LUMINOSIDAD_ADC16_CHANNEL_GROUP);
	value1=((float)resultadoADC)*(vref/4095.0);
	lumADC=(value1*100.0)/vref;
	//volADC=(3.3*resultadoADC)/4095;

	return (lumADC);
}

void sensorLum_ini(void){

}

void Sensorlum_Task_Run(void){
	adc_sensor_de_lum=sensorLuminosidadObtenerDato();
}


