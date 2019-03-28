/*
 * rtthread.c
 *
 *  Created on: 2019年3月28日
 *      Author: work
 */

#include "rtthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* 内存管理函数重定义 */
void *rt_malloc(rt_size_t nbytes)
{
	return malloc(nbytes);
}

void rt_free(void *ptr)
{
	free(ptr);
}

void *rt_realloc(void *ptr, rt_size_t nbytes)
{
	return realloc(ptr,nbytes);
}

void *rt_calloc(rt_size_t count, rt_size_t size)
{
	return calloc(count,size);
}

void *rt_memset(void *src, int c, rt_ubase_t n)
{
	return memset(src,c,n);
}

void *rt_memcpy(void *dest, const void *src, rt_ubase_t n)
{
	return memcpy(dest,src,n);
}

rt_int32_t rt_strncmp(const char *cs, const char *ct, rt_ubase_t count)
{
	return strncmp(cs,ct,count);
}

rt_int32_t rt_strcmp(const char *cs, const char *ct)
{
	return strcmp(cs,ct);
}

rt_size_t rt_strlen(const char *src)
{
	return strlen(src);
}

char *rt_strdup(const char *s)
{
	return strdup(s);
}

char *rt_strstr(const char *str1, const char *str2)
{
	return strstr(str1,str2);
}

char *rt_strncpy(char *dest, const char *src, rt_ubase_t n)
{
	return strncpy(dest,src,n);
}

void *rt_memmove(void *dest, const void *src, rt_ubase_t n)
{
	return memmove(dest,src,n);
}

rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_ubase_t count)
{
	return memcmp(cs,ct,count);
}

rt_uint32_t rt_strcasecmp(const char *a, const char *b)
{
	return strcasecmp(a,b);
}

void rt_kprintf(char* format, ...)
{
	int* args = (char*)&format + 4;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) == 'c')
			{
				putc((char)args, stdout);
				(char*)args++;
			}
			else if (*(format + 1) == 'd' || *(format + 1) == 'i')
			{
				char buffer[64] = { 0 };
				int i = *args;
				itoa(i, buffer, 10);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 'o')
			{
				char buffer[64] = { 0 };
				int i = *args;
				itoa(i, buffer, 8);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 'x')
			{
				char buffer[64] = { 0 };
				int i = *args;
				itoa(i, buffer, 16);
				char *pstr = buffer;
				while (*pstr) putc(*pstr++, stdout);
				args += 1;
			}
			else if (*(format + 1) == 's')
			{
				char* str = *args;
				while (*str) putc(*str++, stdout);
				args += 1;
			}
			else
			{
				putc(*format, stdout);
				format++;
				continue;
			}
			format += 2;
		}
		else
		{
			putc(*format++, stdout);
		}
	}
}


