#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "blackListIps.h"
uint16_t black_listed_ips_array_lenth = 0;
uint32_t *black_listed_ips_int;

void initblacklistips(){


    const char *black_listed_ips[] = {
            "127.0.0.1",
            "10.10.10.10",
            "10.10.3.47",
            "10.10.3.9",

    };
    black_listed_ips_array_lenth = sizeof(black_listed_ips) / sizeof(black_listed_ips[0]);
    uint32_t ipint[black_listed_ips_array_lenth];
    ipto_int(ipint,black_listed_ips,black_listed_ips_array_lenth);
    black_listed_ips_int = ipint;

//	for (int i = 0; i < black_listed_ips_array_lenth; ++i) {
//
//		printf("iiiii>%d\n",ipint[i]);
//
//	}

}




void ipto_int(uint32_t *ipint,const char *ips[],uint16_t array_lenth){


    for (int i = 0; i < array_lenth; ++i) {

        ipint[i] = ntohl(inet_addr(ips[i]));

    }


}

bool check_ip_is_black_listed(uint32_t ip){


//	printf("this i just the print %d\n",black_listed_ips_array_lenth);

    for (int i = 0; i < black_listed_ips_array_lenth; ++i) {

        if(ip == black_listed_ips_int[i])
            return false;

//		printf("iiiii>%d\n",black_listed_ips_int[i]);

    }

    return true;
}
