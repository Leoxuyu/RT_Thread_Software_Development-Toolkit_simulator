/*
 * LIFO.c
 *
 *  Created on: 2019Äê3ÔÂ28ÈÕ
 *      Author: work
 */

#include "LIFO.h"

rt_err_t LIFO_Init(LIFO_Stack *lifo,rt_uint32_t size)
{
	lifo->base=(rt_uint8_t*)rt_malloc(size);
	if(lifo->base==RT_NULL)
	{
		return RT_FALSE;
	}
	lifo->size=size;
	lifo->top=lifo->base;
	return RT_TRUE;
}

rt_bool_t is_LIFO_Empty(LIFO_Stack *lifo)
{
	if(lifo->base==lifo->top)
	{
		return RT_TRUE;
	}
	return RT_FALSE;
}

rt_bool_t is_LIFO_Full(LIFO_Stack *lifo)
{
	if((lifo->base+lifo->size)<=(lifo->top))
	{
		return RT_TRUE;
	}
	return RT_FALSE;
}

rt_bool_t LIFO_PushElement(LIFO_Stack *lifo,rt_uint8_t data)
{
	if(is_LIFO_Full(lifo))
	{
		return RT_FALSE;
	}
	*(lifo->top)=data;
	lifo->top++;
	return RT_TRUE;
}
rt_bool_t LIFO_PopElement(LIFO_Stack *lifo,rt_uint8_t *data)
{
	if(is_LIFO_Empty(lifo))
	{
		return RT_FALSE;
	}
	lifo->top--;
	*data=*(lifo->top);
	return RT_TRUE;
}

void LIFO_Clean(LIFO_Stack *lifo)
{
	rt_memset(lifo->base,'\0',lifo->size);
	lifo->top=lifo->base;
}
void LIFO_Destory(LIFO_Stack *lifo)
{
	rt_free(lifo->base);
	lifo->base=RT_NULL;
	lifo->top=RT_NULL;
	lifo->size=0;
}












