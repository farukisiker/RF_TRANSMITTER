/*
 * rfid.c
 *
 *  Created on: Nov 23, 2022
 *      Author: mfaruk
 */
#include "rfid.h"
#include "main.h"
#define PULSE_LENGTH 350
extern TIM_HandleTypeDef htim1;

static const char* data = "000000100001010100111111";
static void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < (us*PULSE_LENGTH));  // wait for the counter to reach the us input in the parameter
}

static void preamble(void)
{
	HAL_GPIO_WritePin(rf_tx_GPIO_Port, rf_tx_Pin, 1);
	delay_us(1);
	HAL_GPIO_WritePin(rf_tx_GPIO_Port, rf_tx_Pin, 0);
	delay_us(31);
}
static void data_high(void)
{
	HAL_GPIO_WritePin(rf_tx_GPIO_Port, rf_tx_Pin, 1);
	delay_us(3);
	HAL_GPIO_WritePin(rf_tx_GPIO_Port, rf_tx_Pin, 0);
	delay_us(1);
}
static void data_low(void)
{
	HAL_GPIO_WritePin(rf_tx_GPIO_Port, rf_tx_Pin, 1);
	delay_us(1);
	HAL_GPIO_WritePin(rf_tx_GPIO_Port, rf_tx_Pin, 0);
	delay_us(3);
}

void rf_transmit(const char* data,uint16_t len)
{
	uint16_t i = 0;
//	for (int var = 0; var < 1; ++var) {
//
//	}
	preamble();
	while(i<len)
	{
		if(data[i] == '0')	data_low();
		else				data_high();

		i++;
	}
}

void send_rfid_as_uint32(unsigned long code, unsigned int length) {
  for (int nRepeat = 0; nRepeat < 10; nRepeat++) {
    for (int i = length-1; i >= 0; i--) {
      if (code & (1L << i))
        data_high();
      else
        data_low();
    }
    preamble();
  }
}

void send_rfid_as_char(const char* sCodeWord) {
  // turn the tristate code word into the corresponding bit pattern, then send it
  unsigned long code = 0;
  unsigned int length = 0;
  for (const char* p = sCodeWord; *p; p++) {
    code <<= 1L;
    if (*p != '0')
      code |= 1L;
    length++;
  }
  send_rfid_as_uint32(code, length);
}
