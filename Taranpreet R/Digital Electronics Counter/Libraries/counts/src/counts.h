#pragma once

#include "Arduino.h"
#include "STM32LowPower.h"

// Constants and Macros

#define FAILED 0
#define SUCCESS 1
#define TRUE 1
#define FALSE 0

#define P1 PB0
#define P2 PB1
#define P3 PB2
#define P4 PB3
#define P5 PB4
#define P6 PB5
#define P7 PB6
#define P8 PB7
#define P9 PB8
#define P10 PB9

#define PBR PB13
#define PBS PB15

#define ACT1 PA0
#define ACT2 PA1
#define ACT3 PA2
#define ACT4 PA3
#define ACT5 PA4
#define ACT6 PA5
#define ACT7 PA6
#define ACT8 PA7
#define ACT9 PA8
#define ACT10 PA9

#define PBST PA14

#define TIMEOUT 5000


extern "C"
{
	// Public functions
	uint8_t init_counts();
	uint8_t check_new_round();
	uint8_t check_play();
	uint8_t check_stop();
	uint8_t check_BLE_mode();
	uint8_t check_sleep();
	uint8_t check_start_button();
	uint8_t check_stop_button();
	uint8_t check_reset_button();
	uint8_t check_button(uint32_t button);
	uint8_t toggle_led(uint32_t led);

	// Private functions
	static void StartISR();
	static void WakeupISR();
	static uint8_t WaitButtonReturn(uint32_t led);
	static void PrintBelow10(uint32_t led);	
	static void PrintAbove10(uint32_t led);
	static uint8_t ReadResponse();						

}