/*
 * sensor_sht31.h
 *
 *  Created on: 15/12/2021
 *      Author: Ivan Zagarra
 */

#ifndef IOT_SDK_PERIPHERALS_SENSOR_SHT31_H_
#define IOT_SDK_PERIPHERALS_SENSOR_SHT31_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sdk_hal_i2c1.h"


/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define SHT3X_ADDRESS  (0x44) //!< Default SHT3X I2C address

/*! @brief Listado de registros del sensor SHT3X */
enum _sht3x_commands{
	SHT3X_CMD_PERIODIC_DATA_ACQUISITION_MODE=0x2032,
	SHT3X_CMD_PERIODIC_MEASUREMENT_WITH_ART=0x2B32,
	SHT3X_CMD_FETCH_DATA=0xE000,
	SHT3X_CMD_BREAK=0x3093,
	SHT3X_CMD_SOFT_RESET=0x30A2,
	SHT3X_CMD_HEATER_ENABLED=0x306D,
	SHT3X_CMD_HEATER_DISABLED=0x3066,
	SHT3X_CMD_READ_OUT_STATUS_REGISTER=0xF32D,
	SHT3X_CMD_CLEAR_STATUS_REGISTER=0x3041,
};

/*! @brief Listado de bits que integran el registro status del sensor SHT3X */
typedef struct _sht3x_status_reg {
	uint16_t write_data_checksum :1;
	uint16_t command :1;
	uint16_t reserved_2_3 :2;
	uint16_t system_reset_detected :1;
	uint16_t reserved_5_9 :5;
	uint16_t temp_tracking_alert :1;
	uint16_t rh_tracking_alert :1;
	uint16_t reserved_12 :1;
	uint16_t heater :1;
	uint16_t reserved_14 :1;
	uint16_t alert_pending :1;
} sht3x_status_reg;

/*!
 * @brief Define tipo de datos estructura que permite organizar los datos del sensor SHT3X
 */
typedef struct _sht3x_data{
	uint16_t temperatura;
	uint8_t crc_temperatura;
	uint16_t humedad;
	uint8_t crc_humedad;
}sht3x_data_t;

//Define interconexión entre capa de firmware Peripherals (PPH) y HardwareAbstractionLayer (HAl)
#define sht3xWriteByte	i2c1MasterWriteByte
#define sht3xReadByte	i2c1MasterReadByte

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/

status_t sht3xReadData(sht3x_data_t *data);
status_t sht3xInit(void);
float st3xObtenerDatoTemp(void);
float st3xObtenerDatoHum(void);
void SensorSTH31_Humedad_Task_Run(void);
void SensorSTH31_Temperatura_Task_Run(void);
#include "sensor_sht31.h"

/** @} */ // end of X group
/** @} */ // end of X group


#endif /* IOT_SDK_PERIPHERALS_SENSOR_SHT31_H_ */
