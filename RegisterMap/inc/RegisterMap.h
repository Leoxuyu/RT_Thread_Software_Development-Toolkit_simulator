/*
 * RegisterMap.c
 *
 *  Created on: 2019年3月27日
 *      Author: work
 */

#ifndef INC_REGISTERMAP_C_
#define INC_REGISTERMAP_C_

#include "rtthread.h"

/* 使用数据持久化接口 */
#define REG_MAP_USING_DATA_PERSISTENCE

/* 寄存器名称字符串长度最大值 */
#define REG_NAME_LEN_MAX			0x0010

/* 寄存器存储数据的类型 */
typedef enum
{
	NO_DATA,
	IEEE32,
	UINT_32B,
	UINT_16B,
	UINT_8B,
	BOOLEAN
}DataType_t;

//定义链表节点信息结构体
struct REG_NODE
{
	struct REG_NODE *next;	//指向下一个节点地址
	char NAME[REG_NAME_LEN_MAX];			//寄存器名称
	int Address;			//数据地址
	DataType_t DataType;	//类型 数据类型
	int DATA;				//外部用户传递数据
	struct REG_NODE *prev;	//指向上一个节点地址
};

//抽象数据类型
typedef struct REG_MAP_t
{
    struct REG_NODE head;	//数据
    int num;				//链表数目
}REG_MAP;


REG_MAP *REG_MAP_Create(void);
//增
rt_err_t REG_MAP_Append(char *name,int address,DataType_t type,int data, REG_MAP *handle);
rt_err_t REG_MAP_Prevend(char *name,int address,DataType_t type,int data, REG_MAP *handle);

//查
int REG_MAP_Find_Data_By_Address(int address,REG_MAP *handle);
int REG_MAP_Find_Data_By_Name(const char *name,REG_MAP *handle);
DataType_t REG_MAP_Find_Type_By_Address(int address,REG_MAP *handle);
DataType_t REG_MAP_Find_Type_By_Name(const char *name,REG_MAP *handle);

//改
rt_err_t REG_MAP_Modify_Data_By_Address(int address,int data,REG_MAP *handle);
rt_err_t REG_MAP_Modify_Data_By_Name(const char *name,int data,REG_MAP *handle);
rt_err_t REG_MAP_Modify_Type_By_Address(int address,DataType_t type,REG_MAP *handle);
rt_err_t REG_MAP_Modify_Type_By_Name(const char *name,DataType_t type,REG_MAP *handle);

//删
rt_err_t REG_MAP_Del_By_Address(int address, REG_MAP *handle);
rt_err_t REG_MAP_Del_By_Name(const char *name, REG_MAP *handle);

//销毁
void REG_MAP_Destroy(REG_MAP *handle);

void REG_MAP_Test(void);

void Print_REG_MAP(REG_MAP *handle);


#endif /* INC_REGISTERMAP_C_ */
