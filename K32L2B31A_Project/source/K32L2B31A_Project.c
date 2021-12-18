
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "stdbool.h"
#include "leds.h"
#include "modem.h"
#include "reles.h"
#include "sensor_luminosidad.h"
//#include "sensor_temperatura.h"
//#include "sensor_presion.h"
#include "irq_lptmr0.h"
#include "irq_lpuart0.h"
#include "sdk_hal_i2c1.h"
#include "sensor_sht31.h"


void waytTime(void) {
	uint32_t tiempo = 0x1FFFF;
	do {
		tiempo--;
	} while (tiempo != 0x0000);
}


#define HABILITAR_SENSOR_SHT3X		1


// Para modulo Alarma //
volatile uint32_t segAct=0;

// Inicializa Alarma //
void Alarma_Init(void){
	segAct = lptmr0_irq_counter;
}

// retorna el tiempo futuro de la alarma //
uint32_t Alarma_Set(uint32_t time2Wait){
	segAct = lptmr0_irq_counter;
	return (segAct + time2Wait);
}

// retorna si la alarma se cumplio //
char Alarma_Elapsed(uint32_t time2Test){
	 segAct = lptmr0_irq_counter;

	if(segAct >= time2Test) return true;
	else return false;
}

#define Timer_Init() LPTMR_StartTimer(LPTMR0)

/* Init board hardware. */
void BOARD_Init(void){
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    	BOARD_InitDebugConsole();

#endif

}

int main(void) {
	BOARD_Init();
    Timer_Init();
    Modem_Init();
    Key_Task_Init();
    //sensorTe_ini();
    //sensorPe_ini();
    sensorLum_ini();
    apagar_rele_IN1();
    apagar_rele_IN2();
    //Alarma_Init();
    sht3x_data_t sht3x_datos;
    	uint8_t sht3x_detectado=0;
    	uint8_t sht3x_base_de_tiempo=0;
    	float temp_float;
    		float valor_temp;
    		float hum_float;
    		float valor_hum;
    		float lum;
    		bool estado1;
    		bool estado2;


    printf("Inicializa I2C1:");
       //inicializa puerto I2C1 y solo avanza si es exitoso el proceso
       if(i2c1MasterInit(100000)!=kStatus_Success){	//100kbps
       	printf("Error");
       	return 0 ;
       }
       printf("OK\r\n");


   #if HABILITAR_SENSOR_SHT3X
       printf("Detectando SHT3X:");
       //LLamado a funcion que identifica sensor SHT3X
       if(sht3xInit()== kStatus_Success){
       	sht3x_detectado=1;
       	printf("OK\r\n");
       }
   #endif



    	while(1) {

    		waytTime();
    		Modem_Task_Run();
    		Key_Task_Run();

    		estado1 = boton1LeerEstado();
    		estado2 = boton2LeerEstado();

    		if(estado1==false){

    					encender_rele_IN1();


    				}
    		if(estado2==false){

    			apagar_rele_IN1();


    		    				}

    		/*else{
    					apagar_rele_IN1();
    					    apagar_rele_IN2();
    				}

*/
    		//encender_rele_IN1();
    				 //encender_rele_IN2();

    		lum = sensorLuminosidadObtenerDato();
    		//printf("valor lum %f\r\n",lum);
    		Sensorlum_Task_Run();
    		//hum = sensorPresionObtenerDato();


#if HABILITAR_SENSOR_SHT3X
    	if(sht3x_detectado==1){
    		sht3x_base_de_tiempo++; //incrementa base de tiempo para tomar dato sensor SHT3X
			if(sht3x_base_de_tiempo>2){//	>10 equivale aproximadamente a 2s
				sht3x_base_de_tiempo=0; //reinicia contador de tiempo
	    		if (sht3xReadData(&sht3x_datos) == kStatus_Success) {//toma lectura humedad, temperatura

	    			/*temp_float = st3xObtenerDatoTemp();
	    			printf("valor temp %f, ",temp_float);
	    			hum_float = st3xObtenerDatoHum();
	    			printf("valor hum %f\r\n",hum_float);

	    			SensorSTH31_Temperatura_Task_Run();
	    			SensorSTH31_Humedad_Task_Run();
*/
	    			temp_float = (float)sht3x_datos.temperatura;
	    			valor_temp = -55 + ((175*(temp_float))/65535);


	    			hum_float = (float)sht3x_datos.humedad;
	    			valor_hum = (100 * ((hum_float)/65535))+10;


	    			//printf("SHT3X ->");
	    			//printf("temperatura:%.2f ",valor_temp);	//imprime temperatura sin procesar
	    			//printf("CRC8_t:%d ",sht3x_datos.crc_temperatura);	//imprime CRC8 de temperatura
	    		//printf("humedad:%.2f ",valor_hum);	//imprime humedad sin procesar
        			//printf("CRC8_h:%d ",sht3x_datos.crc_humedad);	//imprime CRC8 de temperatura
        			//printf("\r\n");	//Imprime cambio de linea

        			//printf("Enviando mensaje MQTT por modem EC25\r\n");
        			ec25sensor(valor_temp,valor_hum, lum);

	    		}
			}
    	}
#endif


		}

    return 0 ;

}
