/*
 * ds18b20.h
 *
 *  Created on: Jul 11, 2021
 *      Author: KEPLER296
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#define READ_ROM 	0x33
#define MATH_ROM 	0x55
#define SKIP_ROM 	0xCC
#define ALRM_SRC 	0xEC
#define COVERT_T 	0x44
#define WR_NOTPD 	0x4E
#define RD_NOTPD 	0xBE
#define CP_NOTPD 	0x48
#define RCALL_E2 	0xB8
#define RD_POWER 	0xB4

#define RESOL_9BIT 	0x1F
#define RESOL_10BIT	0x3F
#define RESOL_11BIT 0x5F
#define RESOL_12BIT 0x7F

#define SKIP 		0x00
#define NO_SKIP 	0x01
#define SUM_SENS 	0x04
#define ALL_SENS 	0x0F

#define MAX_TEMP	0x64
#define MIN_TEMP	0x9E

void init_sens( uint8_t mode, uint8_t *rx_state, uint8_t length );
void rx_sens( uint8_t *ptr_data, int length );
void tx_sens( uint8_t byte, uint8_t number_sens );


#endif /* INC_DS18B20_H_ */







