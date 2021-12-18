

#include "sensor_sht31.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
float resultado_humedad_sth31;
float resultado_temperatura_sth31;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
 status_t sht3xSendCommand(uint16_t command_to_send){
 	status_t status;
 	uint8_t i2c_data;
 	uint8_t i2c_addr;

 	i2c_addr =  (uint8_t)(command_to_send>>8);
 	i2c_data = (uint8_t) (command_to_send);

 	status = sht3xWriteByte(&i2c_data, 1, SHT3X_ADDRESS, i2c_addr, 1);

 	return(status);
 }
/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 //------------------------------------
status_t sht3xInit(void) {
	status_t status;
	status=sht3xSendCommand(SHT3X_CMD_PERIODIC_MEASUREMENT_WITH_ART);
	return (status);
}
 //------------------------------------
status_t sht3xReadData(sht3x_data_t *data) {
	status_t status;
	uint8_t i2c_data[8];

	status = sht3xReadByte(&i2c_data[0], 6, SHT3X_ADDRESS, SHT3X_CMD_FETCH_DATA, 2);

	if (status == kStatus_Success) {
		data->temperatura = (uint16_t) (i2c_data[0] << 8);
		data->temperatura |= (uint16_t) (i2c_data[1]);
		data->crc_temperatura=i2c_data[2];

		data->humedad = (uint32_t) (i2c_data[3] << 8);
		data->humedad |= (uint32_t) (i2c_data[4]);
		data->crc_humedad=i2c_data[5];

		return (kStatus_Success);
	} else {
		return (status);
	}
}

float st3xObtenerDatoTemp(void){

	 sht3x_data_t sht3x_datos;
	    	float temp_float;
	    		float valor_temp;

		    			temp_float = (float)sht3x_datos.temperatura;
		    			valor_temp = -55 + ((175*(temp_float))/65535);

	return (valor_temp);
}

float st3xObtenerDatoHum(void){

	 sht3x_data_t sht3x_datos;
	    		float hum_float;
	    		float valor_hum;

		    			hum_float = (float)sht3x_datos.humedad;
		    			valor_hum = (100 * ((hum_float)/65535))+10;

	return (valor_hum);
}

void SensorSTH31_Humedad_Task_Run(void){
	resultado_humedad_sth31 = st3xObtenerDatoHum();
}

void SensorSTH31_Temperatura_Task_Run(void){
	resultado_temperatura_sth31 = st3xObtenerDatoTemp();
}

