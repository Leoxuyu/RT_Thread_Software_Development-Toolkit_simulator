/*
 * FIFO.h
 *
 *  Created on: 2019年3月28日
 *      Author: work
 */

#ifndef DATA_STRUCTURE_INC_FIFO_H_
#define DATA_STRUCTURE_INC_FIFO_H_

#include "rtthread.h"

typedef struct
{
	rt_uint32_t size;
	//数据指针，到时候申请一块内存存放数据
	rt_uint8_t *data_p;
	int front; //指向队头的索引，这个所指的空间不存放元素
	int tail; //指向队尾的索引，存放最后一个元素
}FIFO_Queue;


rt_err_t FIFO_Init(FIFO_Queue *fifo,rt_uint32_t size);
rt_bool_t FIFO_PushElement(FIFO_Queue *fifo,rt_uint8_t data);
rt_bool_t FIFO_PopElement(FIFO_Queue *fifo,rt_uint8_t *data);

void FIFO_Clean(FIFO_Queue *fifo);
void FIFO_Destory(FIFO_Queue *fifo);









#endif /* DATA_STRUCTURE_INC_FIFO_H_ */
