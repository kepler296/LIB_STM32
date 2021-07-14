/*
 * ds18b20.h
 *
 *  Created on: Jul 11, 2021
 *      Author: KEPLER296
 */

#include "main.h"
#include "ds18b20.h"

void search_sens( uint8_t *arr, int length );
void to_bin_byte( uint8_t byte, uint8_t *arr, uint8_t length );
uint8_t pull_data( uint8_t number_sens );
void push_data( uint8_t bit, uint8_t number_sens );

void init_sens( uint8_t mode, uint8_t *rx_state, uint8_t length )
{
	search_sens( rx_state, length );

	for( int i = 0; i < 4; i++ )
	{
		if( rx_state[i] == 0 )
		{
			tx_sens(mode, i);
			tx_sens(WR_NOTPD, i );
			tx_sens(MAX_TEMP, i );
			tx_sens(MIN_TEMP, i );
			tx_sens(RESOL_12BIT, i );
		}
	}
}

void rx_sens( uint8_t *ptr_data, int length )
{
	for( int i = 0; i < length; i++ )
	{
		for( int j = 0; j < 8; j++ )
		{
			ptr_data[i] += pull_data(i) << j;
		}
	}
}

void tx_sens( uint8_t byte, uint8_t number_sens )
{
	for (uint8_t i = 0; i < 8; i++)
	{
		push_data( ( byte & (1 << i) ), number_sens );
		//Delay ???
		delay_micros(5);
	}
}

void to_bin_byte( uint8_t byte, uint8_t *arr, uint8_t length )
{
	for(int i = 0; i < length; i++)
	{
		arr[i] = (byte % 2 == 0) ? 0 : 1;
		byte = byte / 2;
	}
}

uint8_t pull_data( uint8_t number_sens )
{
	GPIOA->ODR &= ~(1 << number_sens);
	delay_micros(2);
	GPIOA->ODR |= (1 << number_sens);
	delay_micros(13);
	uint8_t bit = GPIOA->IDR & (1 << number_sens) ? 1 : 0;
	delay_micros(45);
	return bit;
}

void push_data( uint8_t bit, uint8_t number_sens )
{
	GPIOA->ODR &= ~(1 << number_sens);
	delay_micros(bit ? 3 : 65);
	GPIOA->ODR |= (1 << number_sens);
	delay_micros(bit ? 65 : 3);
}

void search_sens( uint8_t *arr, int length )
{
	uint8_t state_sens = 0x00;

	GPIOA -> BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR1 | GPIO_BSRR_BR2 | GPIO_BSRR_BR3;
	delay_micros(485);
	GPIOA -> BSRR = GPIO_BSRR_BS0 | GPIO_BSRR_BS1 | GPIO_BSRR_BS2 | GPIO_BSRR_BS3;
	delay_micros(65);
	state_sens = GPIOA->IDR & ( ALL_SENS << 0 );
	delay_micros(500);

	to_bin_byte( state_sens, arr, length );
}













