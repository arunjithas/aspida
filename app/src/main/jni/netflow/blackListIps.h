/*
 * blackListIps.h
 *
 *  Created on: 22-Mar-2024
 *      Author: babayaga
 */

#ifndef SRC_BLACKLISTIPS_H_
#define SRC_BLACKLISTIPS_H_


#include <stdbool.h>
#include <stdint.h>

void initblacklistips();
bool check_ip_is_black_listed(uint32_t ip);
void ipto_int(uint32_t *ipint,const char *ips[],uint16_t array_lenth);




#endif /* SRC_BLACKLISTIPS_H_ */
