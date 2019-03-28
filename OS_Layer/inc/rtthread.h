/*
 * rtthread.h
 *
 *  Created on: 2019年3月28日
 *      Author: work
 */

#ifndef OS_LAYER_INC_RTTHREAD_H_
#define OS_LAYER_INC_RTTHREAD_H_

#include "rtconfig.h"
#include "rtdef.h"

/* 内存管理函数重定义 */
void *rt_malloc(rt_size_t nbytes);
void rt_free(void *ptr);
void *rt_realloc(void *ptr, rt_size_t nbytes);
void *rt_calloc(rt_size_t count, rt_size_t size);
void *rt_memset(void *src, int c, rt_ubase_t n);
void *rt_memcpy(void *dest, const void *src, rt_ubase_t n);

/* 字符串操作函数重定义 */
rt_int32_t rt_strncmp(const char *cs, const char *ct, rt_ubase_t count);
rt_int32_t rt_strcmp(const char *cs, const char *ct);
rt_size_t rt_strlen(const char *src);
char *rt_strdup(const char *s);
char *rt_strstr(const char *str1, const char *str2);
char *rt_strncpy(char *dest, const char *src, rt_ubase_t n);
void *rt_memmove(void *dest, const void *src, rt_ubase_t n);
rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_ubase_t count);
rt_uint32_t rt_strcasecmp(const char *a, const char *b);

void rt_kprintf(char* format, ...);

#endif /* OS_LAYER_INC_RTTHREAD_H_ */
