
#ifndef MODEM__HH
#define MODEM__HH

#define TIME_WAIT_RTA_CMD 4 //[=] Segundos que espera una Respuesta del Modem
							//despues de enviar un comando

#define Modem_Send_Cmd(comandoStr) printf(comandoStr)

// Incicializa variables y estado inicial del Modem
// configura y inicia proceso de enviar un primer mensaje

void Modem_Init(void);
void ec25sensor(float valor_temp, float valor_hum, float lum);

// Funcion de estado estable
void Modem_Task_Run(void);

#endif
