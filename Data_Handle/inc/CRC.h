/*
 * CRC.h
 *
 *  Created on: 2019Äê3ÔÂ27ÈÕ
 *      Author: work
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

#include "rtthread.h"

rt_uint16_t CRC16_CALC(rt_uint8_t *buffer, rt_uint16_t crc_length);
rt_err_t CRC16_CHECK(rt_uint8_t *msg,int msg_length,rt_uint16_t CheckedValue);

#endif /* INC_CRC_H_ */
