

#ifndef SRC_SNIFFERENTRYPOINT_H_
#define SRC_SNIFFERENTRYPOINT_H_
// Network Data Structures

#include "v9NetflowData.h"


// Definitions for certain ether types
#define IPv4_TYPE 2048
#define IPv6_TYPE 34525



bool sniff_packet_verbose( uint8_t *ptr, size_t len);

int sniff_packet_proc( uint8_t *ptr,  zdtun_pkt_t *pkt, size_t len);



#endif /* SRC_SNIFFERENTRYPOINT_H_ */
