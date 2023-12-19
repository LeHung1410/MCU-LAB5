/*
 * fsm.c
 *
 *  Created on: Dec 7, 2023
 *      Author: M S I
 */
#include "fsm.h"


uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

int status = INIT;
uint8_t flag = INIT;
uint8_t data[MAX_DATA_SIZE];
uint8_t data_index = 0;
int ADC_value = 0;

int isRST(uint8_t str[]){
	if (str[0] == 'R' && str[1] == 'S' && str[2] == 'T'){
		return 1;
	}
	return 0;
}

int isOK(uint8_t str[]){
	if (str[0] == 'O' && str[1] == 'K'){
		return 1;
	}
	return 0;
}

void command_parser_fsm(ADC_HandleTypeDef* hadc1, UART_HandleTypeDef* huart2){
	char str[50];
	switch(status){
		case INIT:
			if(temp == '!') status = DOING;
			break;
		case DOING:
			if(temp != '!'){
				data[data_index++] = temp;
				if(temp == '#'){
					status = CHECKING;
					data_index = 0;
				}
			}
			break;
		case CHECKING:
			if(isRST(data) == 1){
				flag = RST;
				ADC_value = HAL_ADC_GetValue(hadc1);
				HAL_UART_Transmit (huart2,(void*)str,sprintf(str,"!ADC= %d\r\n",ADC_value),500);
				setTimer1(300);
			}
			else if(isOK(data) == 1){
				flag = INIT;
			}
			status = INIT;
			break;
		default:
			break;
	}
}

void uart_communication_fsm(ADC_HandleTypeDef* hadc1, UART_HandleTypeDef* huart2){
	char str[50];
	switch(flag){
		case INIT:
			break;
		case RST:
			if(timer1_flag == 1){
				ADC_value = HAL_ADC_GetValue(hadc1);
				HAL_UART_Transmit (huart2,(void*)str,sprintf(str,"!ADC= %d\r\n",ADC_value),500);
				setTimer1(300);
			}
			break;
		default:
			break;
	}
}
