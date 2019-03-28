/*
 * main.c
 *
 *  Created on: 2019年3月28日
 *      Author: work
 */

#include "rtthread.h"
#include "cJSON.h"

void cJSON_Test(void)
{
	cJSON_hook_init();
    cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();
    cJSON * next =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "rc", cJSON_CreateNumber(0));//根节点下添加
    cJSON_AddItemToObject(root, "operation", cJSON_CreateString("CALL"));
    cJSON_AddItemToObject(root, "service", cJSON_CreateString("telephone"));
    cJSON_AddItemToObject(root, "text", cJSON_CreateString("打电话给张三"));
    cJSON_AddItemToObject(root, "semantic", item);//root节点下添加semantic节点
    cJSON_AddItemToObject(item, "slots", next);//semantic节点下添加item节点
    cJSON_AddItemToObject(next, "name", cJSON_CreateString("张三"));//添加name节点
    rt_kprintf("%s\n", cJSON_PrintUnformatted(root));
}




int main(void)
{
	cJSON_Test();
}















