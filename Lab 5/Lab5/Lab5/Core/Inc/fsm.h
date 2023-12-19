/*
 * fsm.h
 *
 *  Created on: Dec 7, 2023
 *      Author: M S I
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#define MAX_BUFFER_SIZE  50
#define MAX_DATA_SIZE 50

#define RST 3
#define OK 4

#define INIT 0
#define DOING 1
#define CHECKING 2

#include "main.h"
#include "software_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_FSM_H_ */
