
#ifndef SRC_DATAPARSER_H_
#define SRC_DATAPARSER_H_

#include "datastructur.h"


void
parse_data(const uint8_t *data, size_t size);

void
parse_ether_header(struct ether_header *eh,flowstructur_s *pack);

void
parse_ether_arp(struct ether_arp *ether_arp);

bool
parse_ip(struct ip *ip);

void
parse_ipv6(struct ip6_hdr *ip6_hdr);

void
parse_tcphdr(struct tcphdr *tcphdr,flowstructur_s *pack);

void
parse_tcphdr_port_flag(struct tcphdr *tcphdr,uint8_t *tcp_flags,uint16_t *src_port,uint16_t *dst_port);

void
parse_tcp_optpad(unsigned char *data, int size);

void
parse_udphdr(struct udphdr *udphdr,flowstructur_s *pack);

void
parse_icmp(struct icmp *icmp,flowstructur_s *pack, unsigned char *hptr, int size);

void
parse_icmp_get_ports(struct icmp *icmp,uint16_t *src_port,uint16_t *dst_port,unsigned char *hptr, int size);

#endif /* SRC_DATAPARSER_H_ */
