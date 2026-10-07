
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netdb.h>

#include <ctype.h>
#include <errno.h>
#include <ifaddrs.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include <stdio.h>
#include <netinet/if_ether.h>  // for struct ether_arp
#include <arpa/inet.h>         // for inet_ntoa etc.


#include "dataParser.h"
#include "blackListIps.h"
#include "global.h"
#include "datastructur.h"

#include "common/utils.h"

void
parse_data(const uint8_t *data, size_t size)
{
    int i, j;
    (void) printf("data--------------------------------------------------------"
                  "--------------------\n");
    for (i = 0; i < (int)size; i++) {
        for (j = 0; j < 16; j++) {
            if (j != 0) {
                (void) printf(" ");
            }
            if (i + j < (int)size) {
                (void) printf("%02X", *(data + j));
            } else {
                (void) printf("  ");
            }
        }
        (void) printf("    ");
        for (j = 0; j < 16; j++) {
            if (i < (int)size) {
                if (isascii(*data) && isprint(*data)) {
                    (void) printf("%c", *data);
                } else {
                    (void) printf(".");
                }
                data++;
                i++;
            } else {
                (void) printf(" ");
            }
        }
        (void) printf("\n");
    }
}

void
parse_ether_header(struct ether_header *eh,flowstructur_s *pack)
{
    int i;
    for (i = 0; i<ETHER_ADDR_LEN; i++) {

        pack->in_src_mac[i] = eh->ether_shost[i];
        pack->out_dst_mac[i]  = eh->ether_dhost[i];
    }
    //	printf("ether_header------------------------------------------------"
    //			"--------------------\n");
    //	printf("ether_dhost = ");
    //	for (i = 0; i<ETHER_ADDR_LEN; i++) {
    //
    //		if (i != 0) {
    //			printf(":");
    //		}
    //		printf("%02X", eh->ether_dhost[i]);
    //	}
    //	printf("\n");
    //	printf("ether_shost = ");
    //	for (i = 0; i < ETHER_ADDR_LEN; i++) {
    //		if (i != 0) {
    //			printf(":");
    //		}
    //		printf("%02X", eh->ether_shost[i]);
    //	}
    //	printf("\n");
    //	printf("ether_type = %02X", ntohs(eh->ether_type));
    //	switch(ntohs(eh->ether_type)){
    //	case ETHERTYPE_PUP:
    //		printf("(Xerox PUP)\n");
    //		break;
    //	case ETHERTYPE_IP:
    //		printf("(IP)\n");
    //		break;
    //	case ETHERTYPE_ARP:
    //		printf("(Address resolution)\n");
    //		break;
    //	case ETHERTYPE_REVARP:
    //		printf("(Reverse ARP)\n");
    //		break;
    //	case 0x86DD:
    //		printf("(IPv6)\n");
    //		break;
    //	default:
    //		printf("(unknown)\n");
    //		break;
    //	}
}

//void
//parse_ether_arp(struct ether_arp *ether_arp)
//{
//    static char *hrd[] = {
//            (char *)"From KA9Q: NET/ROM pseudo.",
//            (char *)"Ethernet 10/100Mbps.",
//            (char *)"Experimental Ethernet.",
//            (char *)"AX.25 Level 2.",
//            (char *)"PROnet token ring.",
//            (char *)"Chaosnet.",
//            (char *)"IEEE 802.2 Ethernet/TR/TB.",
//            (char *)"ARCnet.",
//            (char *)"APPLEtalk.",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"Frame Relay DLCI.",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"ATM.",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"undefine",
//            (char *)"Metricom STRIP (new IANA id)."
//    };
//    static char *op[] = {
//            (char *)"undefined",
//            (char *)"ARP request.",
//            (char *)"ARP reply.",
//            (char *)"RARP request.",
//            (char *)"RARP reply.",
//            (char *)"undefined",
//            (char *)"undefined",
//            (char *)"undefined",
//            (char *)"InARP request.",
//            (char *)"InARP reply.",
//            (char *)"(ATM)ARP NAK."
//    };
//    int i;
//    printf("ether_arp---------------------------------------------------"
//           "--------------------\n");
//    printf("arp_hrd = %u", ntohs(ether_arp->arp_hrd));
//    if (ntohs(ether_arp->arp_hrd) <= 23) {
//        printf("(%s), ", hrd[ntohs(ether_arp->arp_hrd)]);
//    } else {
//        printf("(undefined), ");
//    }
//    printf("arp_pro = %u", ntohs(ether_arp->arp_pro));
//    switch(ntohs(ether_arp->arp_pro)){
//        case ETHERTYPE_PUP:
//            printf("(Xerox POP)\n");
//            break;
//        case ETHERTYPE_IP:
//            printf("(IP)\n");
//            break;
//        case ETHERTYPE_ARP:
//            printf("(Address resolution)\n");
//            break;
//        case ETHERTYPE_REVARP:
//            printf("(Reverse ARP)\n");
//            break;
//        default:
//            printf("(unknown)\n");
//            break;
//    }
//    printf("arp_hln = %u, ", ether_arp->arp_hln);
//    printf("arp_pln = %u, ", ether_arp->arp_pln);
//    printf("arp_op = %u", ntohs(ether_arp->arp_op));
//    if (ntohs(ether_arp->arp_op) <= 10) {
//        printf("(%s)\n", op[ntohs(ether_arp->arp_op)]);
//    } else {
//        printf("(undefine)\n");
//    }
//    printf("arp_sha = ");
//    for (i = 0; i<ether_arp->arp_hln; i++) {
//        if (i != 0) {
//            printf(":");
//        }
//        printf("%02X", ether_arp->arp_sha[i]);
//    }
//    printf("\n");
//    printf("arp_spa = ");
//    for (i = 0; i < ether_arp->arp_pln; i++) {
//        if (i != 0) {
//            printf(".");
//        }
//        printf("%u", ether_arp->arp_spa[i]);
//    }
//    printf("\n");
//    printf("arp_tha = ");
//    for (i = 0; i < ether_arp->arp_hln; i++) {
//        if (i != 0) {
//            printf(":");
//        }
//        printf("%02X", ether_arp->arp_tha[i]);
//    }
//    printf("\n");
//    printf("arp_tpa = ");
//    for (i = 0; i < ether_arp->arp_pln; i++) {
//        if (i != 0) {
//            printf(".");
//        }
//        printf("%u", ether_arp->arp_tpa[i]);
//    }
//    printf("\n");
//}

bool
parse_ip(struct ip *ip)
{


    uint32_t ip_src_int = ntohl(ip->ip_src.s_addr);
    if(!check_ip_is_black_listed(ip_src_int)){
        return false;
    }

    char *ip_str = inet_ntoa(ip->ip_dst);

    // Convert the string representation to a 32-bit integer in network byte order
//    uint32_t ip_address = inet_addr(ip_str);
//    if(!check_ip_is_black_listed(ip_address)){
//        return false;
//    }

    static char *proto[] = {
            (char *)"undefined",
            (char *)"ICMP",
            (char *)"IGMP",
            (char *)"undefined",
            (char *)"IPIP",
            (char *)"undefined",
            (char *)"TCP",
            (char *)"undefined",
            (char *)"EGP",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"PUP",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"UDP"
    };



//	int result = strcmp(inet_ntoa(ip->ip_src), "10.10.3.159");
//	if (result == 0){
//
//		printf("ip----------------------------------------------------------"
//				"--------------------\n");
//		printf("ip_v = %u, ", ip->ip_v);
//		printf("ip_hl = %u, ", ip->ip_hl);
//		printf("ip_tos = %x, ", ip->ip_tos);
//		printf("ip_len = %d\n", ntohs(ip->ip_len));
//		printf("ip_id = %u, ", ntohs(ip->ip_id));
//		printf("ip_off = %x, %d\n",
//				(ntohs(ip->ip_off))>>13 & 0x07,
//				ntohs(ip->ip_off)&0x1FFF);
//		printf("ip_ttl = %u, ", ip->ip_ttl);
//		printf("ip_p = %u", ip->ip_p);
//		if (ip->ip_p <= 17) {
//			printf("(%s), ", proto[ip->ip_p]);
//		} else {
//			printf("(undefined), ");
//		}
    log_d("netflow ip_sum = %u\n", ntohs(ip->ip_sum));
    log_d("netflow ip_src = %s\n", inet_ntoa(ip->ip_src));
    log_d("netflow ip_dst = %s\n", inet_ntoa(ip->ip_dst));
//
//		return true;
//	}

    return true;
}

void
parse_ipv6(struct ip6_hdr *ip6_hdr)
{
    char buf[SIZE_OF_IPV6_BUF];
    static char *proto[] = {
            (char *)"undefined",
            (char *)"ICMP",
            (char *)"IGMP",
            (char *)"undefined",
            (char *)"IPIP",
            (char *)"undefined",
            (char *)"TCP",
            (char *)"undefined",
            (char *)"EGP",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"PUP",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"UDP"
    };
    printf("ip6---------------------------------------------------------"
           "--------------------\n");
    printf("ip6_vfc = %u\n", ip6_hdr->ip6_vfc);
    printf("ip6_flow = %u\n", ip6_hdr->ip6_flow);
    printf("ip6_plen = %u\n", ip6_hdr->ip6_plen);
    if (ip6_hdr->ip6_nxt <= 17) {
        printf("(%s), ", proto[ip6_hdr->ip6_nxt]);
    } else {
        printf("(undefined), ");
    }
    printf("ip6_hlim = %u\n", ip6_hdr->ip6_hlim);
    printf("ip6_src = %s\n", inet_ntop(AF_INET6,
                                       &ip6_hdr->ip6_src,
                                       buf,
                                       SIZE_OF_IPV6_BUF
            /*sizeof(buf)*/));
    printf("ip6_dst = %s\n", inet_ntop(AF_INET6,
                                       &ip6_hdr->ip6_dst,
                                       buf,
                                       SIZE_OF_IPV6_BUF
            /*sizeof(buf)*/));
}

void
parse_tcphdr(struct tcphdr *tcphdr,flowstructur_s *pack)
{
    //	printf("tcphdr------------------------------------------------------"
    //			"--------------------\n");
    //
    //	printf("source = %u, ", ntohs(tcphdr->source));
    //	printf("dest = %u\n", ntohs(tcphdr->dest));
    //	printf("seq = %u\n", ntohl(tcphdr->seq));
    //	printf("ack_seq = %u\n", ntohl(tcphdr->ack_seq));
    //	printf("doff = %u, ", tcphdr->doff);
    //	printf("urg = %u, ", tcphdr->urg);
    //	printf("ack = %u, ", tcphdr->ack);
    //	printf("psh = %u, ", tcphdr->psh);
    //	printf("rst = %u, ", tcphdr->rst);
    //	printf("syn = %u, ", tcphdr->syn);
    //	printf("fin = %u, ", tcphdr->fin);
    //	printf("th_win = %u\n", ntohs(tcphdr->window));
    //	printf("th_sum = %u, ", ntohs(tcphdr->check));
    //	printf("th_urp = %u\n", ntohs(tcphdr->urg_ptr));

    pack->l4_src_port = tcphdr->source;
    pack->l4_dst_port = tcphdr->dest;

    pack->tcp_flags |= tcphdr->fin << 0;
    pack->tcp_flags |= tcphdr->syn << 1;
    pack->tcp_flags |= tcphdr->rst << 2;
    pack->tcp_flags |= tcphdr->psh << 3;
    pack->tcp_flags |= tcphdr->ack << 4;
    pack->tcp_flags |= tcphdr->urg << 5;

}


void
parse_tcphdr_port_flag(struct tcphdr *tcphdr,uint8_t *tcp_flags,uint16_t *src_port,uint16_t *dst_port)
{
    //	printf("tcphdr------------------------------------------------------"
    //			"--------------------\n");
    //
    //	printf("source = %u, ", ntohs(tcphdr->source));
    //	printf("dest = %u\n", ntohs(tcphdr->dest));
    //	printf("seq = %u\n", ntohl(tcphdr->seq));
    //	printf("ack_seq = %u\n", ntohl(tcphdr->ack_seq));
    //	printf("doff = %u, ", tcphdr->doff);
    //	printf("urg = %u, ", tcphdr->urg);
    //	printf("ack = %u, ", tcphdr->ack);
    //	printf("psh = %u, ", tcphdr->psh);
    //	printf("rst = %u, ", tcphdr->rst);
    //	printf("syn = %u, ", tcphdr->syn);
    //	printf("fin = %u, ", tcphdr->fin);
    //	printf("th_win = %u\n", ntohs(tcphdr->window));
    //	printf("th_sum = %u, ", ntohs(tcphdr->check));
    //	printf("th_urp = %u\n", ntohs(tcphdr->urg_ptr));

    *src_port = tcphdr->source;
    *dst_port = tcphdr->dest;

    *tcp_flags |= tcphdr->fin << 0;
    *tcp_flags |= tcphdr->syn << 1;
    *tcp_flags |= tcphdr->rst << 2;
    *tcp_flags |= tcphdr->psh << 3;
    *tcp_flags |= tcphdr->ack << 4;
    *tcp_flags |= tcphdr->urg << 5;

}


void
parse_tcp_optpad(unsigned char *data, int size)
{
    int i;
    //	printf("option, pad = ");
    for (i = 0; i < size; i++) {
        //		if (i != 0) {
        //			printf(", ");
        //		}
        //		printf("%x", *data);
        data++;
    }
    //	printf("\n");
}

void
parse_udphdr(struct udphdr *udphdr,flowstructur_s *pack)
{
    //	printf("udphdr------------------------------------------------------"
    //			"--------------------\n");
    //	printf("source = %u, ", ntohs(udphdr->source));
    //	printf("dest = %u\n", ntohs(udphdr->dest));
    //	printf("len = %u, ", ntohs(udphdr->len));
    //	printf("check = %u\n", ntohs(udphdr->check));

    pack->l4_src_port = udphdr->source;
    pack->l4_dst_port = udphdr->dest;
}

void
parse_icmp(struct icmp *icmp,flowstructur_s *pack, unsigned char *hptr, int size)
{
    static char *type[] = {
            (char *)"Echo Reply",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"Destination Unreachable",
            (char *)"Source Quench",
            (char *)"Redirect",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"Echo Request",
            (char *)"Router Adverisement",
            (char *)"Router Selection",
            (char *)"Time Exceeded for Datagram",
            (char *)"Parameter Problem on Datagram",
            (char *)"Timestamp Request",
            (char *)"Timestamp Reply",
            (char *)"Information Request",
            (char *)"Information Reply",
            (char *)"Address Mask Request",
            (char *)"Address Mask Reply"
    };
    struct tcphdr tcphdr;
    struct udphdr udphdr;
    //	printf("icmp--------------------------------------------------------"
    //			"--------------------\n");

    pack->icmp_type = icmp->icmp_type;
    //	printf("icmp_type = %u", icmp->icmp_type);
    //	if (icmp->icmp_type <= 18) {
    //		printf("(%s), ", type[icmp->icmp_type]);
    //	} else {
    //		printf("(undefined), ");
    //	}
    //	printf("icmp_code = %u, ", icmp->icmp_code);
    //	printf("icmp_cksum = %u\n", ntohs(icmp->icmp_cksum));
    //	if (icmp->icmp_type == 0 || icmp->icmp_type == 8) {
    //		printf("icmp_id = %u, ", ntohs(icmp->icmp_id));
    //		printf("icmp_seq = %u\n", ntohs(icmp->icmp_seq));
    ////		parse_data(hptr+8, size-8);
    //	} else if (icmp->icmp_type == 3) {
    //		if (icmp->icmp_code == 4) {
    //			printf("icmp_pmvoid = %u\n", ntohs(icmp->icmp_pmvoid));
    //			printf("icmp_nextmtu = %u\n", ntohs(icmp->icmp_nextmtu));
    //		} else {
    //			printf("icmp_void = %u\n", ntohs(icmp->icmp_void));
    //		}
    //	} else if (icmp->icmp_type == 5) {
    //		printf("icmp_gwaddr = %s\n", inet_ntoa(icmp->icmp_gwaddr));
    //	} else if (icmp->icmp_type == 11) {
    //		printf("icmp_void = %u\n", ntohs(icmp->icmp_void));
    //	}
    if (icmp->icmp_type == 3 || icmp->icmp_type == 5 || icmp->icmp_type == 11) {
        parse_ip(&icmp->icmp_ip);
        if (icmp->icmp_ip.ip_p == IPPROTO_TCP) {
            hptr += 8;
            hptr += IPHDR_LEN; //sizeof(struct ip);
            (void) memcpy(&tcphdr, hptr, TCPHDR_LEN /*sizeof(struct tcphdr)*/);
            parse_tcphdr(&tcphdr,pack);
        } else if(icmp->icmp_ip.ip_p == IPPROTO_UDP) {
            hptr += 8;
            hptr += IPHDR_LEN; //sizeof(struct ip);
            memcpy(&udphdr, hptr, UDPHDR_LEN /*sizeof(struct udphdr)*/);
            parse_udphdr(&udphdr,pack);
        }
    }
}

void
parse_icmp_get_ports(struct icmp *icmp,uint16_t *src_port,uint16_t *dst_port,unsigned char *hptr, int size)
{
    static char *type[] = {
            (char *)"Echo Reply",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"Destination Unreachable",
            (char *)"Source Quench",
            (char *)"Redirect",
            (char *)"undefined",
            (char *)"undefined",
            (char *)"Echo Request",
            (char *)"Router Adverisement",
            (char *)"Router Selection",
            (char *)"Time Exceeded for Datagram",
            (char *)"Parameter Problem on Datagram",
            (char *)"Timestamp Request",
            (char *)"Timestamp Reply",
            (char *)"Information Request",
            (char *)"Information Reply",
            (char *)"Address Mask Request",
            (char *)"Address Mask Reply"
    };
    struct tcphdr tcphdr;
    struct udphdr udphdr;
    //	printf("icmp--------------------------------------------------------"
    //			"--------------------\n");

    if (icmp->icmp_type == 3 || icmp->icmp_type == 5 || icmp->icmp_type == 11) {
        parse_ip(&icmp->icmp_ip);
        if (icmp->icmp_ip.ip_p == IPPROTO_TCP) {
            hptr += 8;
            hptr += IPHDR_LEN; //sizeof(struct ip);
            (void) memcpy(&tcphdr, hptr, TCPHDR_LEN /*sizeof(struct tcphdr)*/);
            *src_port = tcphdr.source;
            *dst_port = tcphdr.dest;


        } else if(icmp->icmp_ip.ip_p == IPPROTO_UDP) {
            hptr += 8;
            hptr += IPHDR_LEN; // sizeof(struct ip);
            memcpy(&udphdr, hptr, UDPHDR_LEN/*sizeof(struct udphdr)*/);
            *src_port = udphdr.source;
            *dst_port = udphdr.dest;

        }
    }
}
