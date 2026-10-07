/*
 * global.h
 *
 *  Created on: 26-Mar-2024
 *      Author: babayaga
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define UDPHDR_LEN sizeof(struct udphdr)

#define TCPHDR_LEN sizeof(struct tcphdr)

#define ICMPHDR_LEN sizeof(struct icmp)


#define IP6_HDR_LEN sizeof(struct ip6_hdr)


#define IPHDR_LEN sizeof(struct ip)

#define ETHER_ARP_HDR_LEN sizeof(struct ether_arp)


#define ETHER_HEADER_LEN sizeof(struct ether_header)

#define SIZE_OF_IPV6_BUF 256



#endif /* INC_GLOBAL_H_ */
