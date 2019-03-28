/*
 * LIFO.h
 *
 *  Created on: 2019Äê3ÔÂ28ÈÕ
 *      Author: work
 */

#ifndef DATA_STRUCTURE_INC_LIFO_H_
#define DATA_STRUCTURE_INC_LIFO_H_

#include "rtthread.h"

typedef struct
{
    rt_uint32_t		*base;
    rt_uint32_t		*top;
    rt_uint32_t		size ;
} LIFO_Stack;

rt_err_t LIFO_Init(LIFO_Stack *lifo,rt_uint32_t size);
rt_bool_t is_LIFO_Empty(LIFO_Stack *lifo);
rt_bool_t LIFO_PushElement(LIFO_Stack *lifo,rt_uint8_t data);
rt_bool_t LIFO_PopElement(LIFO_Stack *lifo,rt_uint8_t *data);
void LIFO_Clean(LIFO_Stack *lifo);
void LIFO_Destory(LIFO_Stack *lifo);

#endif /* DATA_STRUCTURE_INC_LIFO_H_ */
