/*
 * BASE64.c
 *
 *  Created on: 2019Äê3ÔÂ27ÈÕ
 *      Author: xuyu
 */

#include "BASE64.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void safe_free(void *it)
{
	rt_free(it);
	it = RT_NULL;
}

static char b64_to_ascii(char str)
{
    if (str >= 0 && str <= 25)
    {
        return str + 65;
    }
    else if (str >= 26 && str <= 51)
    {
        return str + 71;
    }
    else if (str >= 52 && str <= 61)
    {
        return str - 4;
    }
    else if (str == 62)
    {
        return '+';
    }
    else
    {
        return '/';
    }
}

static char ascii_to_b64(char str)
{
    if (str >= 65 && str <= 90)
    {
        return str - 65;
    }
    else if (str >= 97 && str <= 122)
    {
        return str - 71;
    }
    else if (str >= 48 && str <= 57)
    {
        return str + 4;
    }
    else if (str == '+')
    {
        return 62;
    }
    else
    {
        return 63;
    }
}

static int check_byte(char byte)
{
    if (!((byte >= 'a' && byte <= 'z') || (byte >= 'A' && byte <= 'Z') ||(byte >= '0' && byte <= '9') || byte == '+' || byte == '/'))
    {
    	return 1;
    }
    return 0;
}

static int get_decode_len_from_b64_string(char *string)
{
    int len = 0;
    int i;
    if (!string)
    {
    	return 0;
    }
    len = rt_strlen(string);
    for (i = 0; i < (len - 2); i ++)
    {
        if (string[i] == '=')
        {
        	return 0;
        }
        if (check_byte(string[i]) == 1)
        {
        	return 0;
        }
    }
    if (string[i] == '=')
    {
        if (string[i + 1] != '=')
        {
        	return 0;
        }
        return len / 4 * 3 - 2;
    }
    else
    {
        if (check_byte(string[i]) == 1)
		{
					return 0;
		}
        if (string[i + 1] != '=')
        {
            if (check_byte(string[i + 1]) == 1)
            {
            	return 0;
            }
            return len / 4 * 3;
        }
        return len / 4 * 3 - 1;
    }
}

char *BASE64_encode(char *str)
{
    int slen = 0;
    int encode_len = 0;
    int slen_quotient = 0;
    int slen_remainder = 0;
    int count = 0;
    int i;
    char *string = RT_NULL;
    char *encode_string = RT_NULL;
    string = rt_strdup(str);
    slen = rt_strlen(string);
    slen_quotient = slen / 3;
    slen_remainder = slen % 3;
    encode_len = slen_quotient * 4 + (slen_remainder ? 4 : 0);
    encode_string = rt_malloc(encode_len + 1);
    rt_memset(encode_string,'\0',encode_len + 1);
    for (i = 0; i < slen_quotient * 3; i += 3)
    {
        encode_string[count ++] = b64_to_ascii((string[i] & 0xFF) >> 2);
        encode_string[count ++] = b64_to_ascii(((string[i] & 0x03) << 4) | ((string[i + 1] & 0xFF) >> 4));
        encode_string[count ++] = b64_to_ascii(((string[i + 1] & 0x0F) << 2) | ((string[i + 2] & 0xFF) >> 6));
        encode_string[count ++] = b64_to_ascii(string[i + 2] & 0x3F);
    }

    if (slen_remainder == 1)
    {
        encode_string[count ++] = b64_to_ascii((string[i] & 0xFF) >> 2);
        encode_string[count ++] = b64_to_ascii((string[i] & 0x03) << 4);
        encode_string[count ++] = '=';
        encode_string[count ++] = '=';
    }
    else if (slen_remainder == 2)
    {
        encode_string[count ++] = b64_to_ascii((string[i] & 0xFF) >> 2);
        encode_string[count ++] = b64_to_ascii(((string[i] & 0x03) << 4) | ((string[i + 1] & 0xFF) >> 4));
        encode_string[count ++] = b64_to_ascii((string[i + 1] & 0x0F) << 2);
        encode_string[count ++] = '=';
    }
    safe_free(string);
    return encode_string;
}

char *BASE64_decode(char *str)
{
    int encode_len = 0;
    int decode_len = 0;
    int count = 0;
    int i;
    char *encode_str = RT_NULL;
    char *decode_str = RT_NULL;
    encode_len = rt_strlen(str);
    if (encode_len < 4 || encode_len % 4 != 0)
    {
        printf("error: the length of encode string is invalid!\n");
        return RT_NULL;
    }
    decode_len = get_decode_len_from_b64_string(str);
    if (decode_len == 0)
    {
        printf("error: encode string is invalid!\n");
        return RT_NULL;
    }
    encode_str = rt_strdup(str);
    decode_str = rt_malloc(decode_len + 1);
    rt_memset(decode_str,'\0',decode_len + 1);
    for (i = 0; i < encode_len; i += 4)
    {
        char encode_byte1;
        char encode_byte2;
        char encode_byte3;
        char encode_byte4;
        encode_byte1 = ascii_to_b64(encode_str[i]) & 0xFF;
        encode_byte2 = ascii_to_b64(encode_str[i + 1]) & 0xFF;
        decode_str[count++] = (encode_byte1 << 2) | (encode_byte2 >> 4);
        if (encode_str[i + 2] == '=')
		{
			break;
		}
        encode_byte3 = ascii_to_b64(encode_str[i + 2]) & 0xFF;
        decode_str[count++] = (encode_byte2 << 4) | (encode_byte3 >> 2);
        if (encode_str[i + 3] == '=')
        {
        	break;
        }
        encode_byte4 = ascii_to_b64(encode_str[i + 3]) & 0xFF;
        decode_str[count++] = (encode_byte3 << 6) | encode_byte4;
    }
    safe_free(encode_str);
    return decode_str;
}
