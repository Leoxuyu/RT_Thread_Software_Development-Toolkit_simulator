/*
 * FIFO.c
 *
 *  Created on: 2019Äê3ÔÂ28ÈÕ
 *      Author: work
 */

#include "FIFO.h"

rt_err_t FIFO_Init(FIFO_Queue *fifo,rt_uint32_t size)
{
	rt_uint8_t* queue=(rt_uint8_t *)rt_malloc(size);
	if(queue==RT_NULL)
	{
		return RT_ERROR;
	}
	rt_memset(queue,'\0',size+1);
	fifo->data_p=queue;
	fifo->size=size+1;
	fifo->front=0;
	fifo->tail=0;
	return RT_EOK;
}

rt_bool_t is_FIFO_Empty(FIFO_Queue *fifo)
{
	rt_bool_t ret;
	if (fifo->front == fifo->tail)
	{
		ret=RT_TRUE;
	}
	else
	{
		ret=RT_FALSE;
	}
	return ret;
}

rt_bool_t is_FIFO_Full(FIFO_Queue *fifo)
{
	rt_bool_t ret;
	if ((fifo->tail+1)%(fifo->size)==fifo->front)
	{
		ret=RT_TRUE;
	}
	else
	{
		ret=RT_FALSE;
	}
	return ret;
}

rt_bool_t FIFO_PushElement(FIFO_Queue *fifo,rt_uint8_t data)
{
	if(is_FIFO_Full(fifo))
	{
		return RT_FALSE;
	}
	*(fifo->data_p+fifo->tail)=data;
	fifo->tail=(fifo->tail+1)%(fifo->size);
	return RT_TRUE;
}

rt_bool_t FIFO_PopElement(FIFO_Queue *fifo,rt_uint8_t *data)
{
	if(is_FIFO_Empty(fifo))
	{
		return RT_FALSE;
	}
	*data=*(fifo->data_p+fifo->front);
	fifo->front=(fifo->front+1)%(fifo->size);
	return RT_TRUE;
}

void FIFO_Clean(FIFO_Queue *fifo)
{
	rt_memset(fifo->data_p,'\0',fifo->size);
	fifo->front=0;
	fifo->tail=0;
}

void FIFO_Destory(FIFO_Queue *fifo)
{
	rt_free(fifo->data_p);
	fifo->data_p=RT_NULL;
	fifo->front=0;
	fifo->tail=0;
}

