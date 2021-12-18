
#include "sensor_presion.h"
#include "math.h"
#include <stdio.h>

float adc_sensor_de_pres;

void sensorPresionIniciarCaptura(void); //metodos privados para que no se vean en la libreria principal
void sensorPresionEsperarResultado(void);

void sensorPresionIniciarCaptura(void){
	ADC16_SetChannelConfig(SENSOR_PRESION_ADC16_BASE, SENSOR_PRESION_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[1]);
}

void sensorPresionEsperarResultado(void){
	while (0U == (kADC16_ChannelConversionDoneFlag
			& ADC16_GetChannelStatusFlags(SENSOR_PRESION_ADC16_BASE, SENSOR_PRESION_ADC16_CHANNEL_GROUP))){
	       }

}
float sensorPresionObtenerDato(void){
	sensorPresionIniciarCaptura();
	sensorPresionEsperarResultado();
	uint32_t resultadoADC;
	float lumiADC, value1;
		float vref = 4.7;
		resultadoADC = ADC16_GetChannelConversionValue(SENSOR_PRESION_ADC16_BASE, SENSOR_PRESION_ADC16_CHANNEL_GROUP);
		value1=((float)resultadoADC)*(vref/4095.0);
		lumiADC=(value1*100.0)/vref;
		//volADC=(3.3*resultadoADC)/4095;
	return (lumiADC);
}

void sensorPe_ini(void){

}

void Sensorpres_Task_Run(void){
	adc_sensor_de_pres=sensorPresionObtenerDato();
}

