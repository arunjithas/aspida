#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // type boolean
#include <string.h>
#include <unistd.h>

// standart C stuff
#include <ctype.h>      // isprint()
// used for exiting the program (with ctrl+c etc.) with proper clear
#include <signal.h>
#include <sys/time.h>   // time miliseconds
#include <time.h>       // time()

#include <netinet/ip_icmp.h>   // Provides declarations for icmp header
#include <netinet/udp.h>       // Provides declarations for udp header
#include <netinet/tcp.h>       // Provides declarations for tcp header
#include <netinet/ip.h>        // Provides declarations for ip header
#include <netinet/ip6.h>
#include <netinet/in.h>
#include <netinet/if_ether.h> // For ETH_P_ALL
#include <linux/if_packet.h>  // For sockaddr_ll
#include <net/if.h> 		  // For ifreq
#include <arpa/inet.h>        // inet_ntop()
#include <sys/socket.h>
#include <linux/if_packet.h>  // For struct sockaddr_ll
#include <sys/ioctl.h>
#include <net/ethernet.h>

//#include "third_party/uthash.h"
//#include "third_party/net_headers.h"

#include "common/utils.h"


#include "snifferentrypoint.h"

#include "v9NetflowData.h"
// Network Data Structures
//#include "dataAnalyzer.h"
#include "dataParser.h"
#include "config.h"
#include "global.h"

#define BUFFER_SIZE 65536
#define REPLY_BUF_SIZE 65535
#define DEFAULT_TCP_WINDOW 65535
#define TCP_HEADER_LEN 20
#define IPV4_HEADER_LEN 20
#define IPV6_HEADER_LEN 40
#define UDP_HEADER_LEN 8

#define ICMP_TIMEOUT_SEC 5
#define UDP_TIMEOUT_SEC 30
#define TCP_TIMEOUT_SEC 60

static struct timeval flow_time_finder;

int sock_raw;
int tcp = 0, udp = 0, icmp = 0, others = 0, igmp = 0, total = 0, i, j;

struct sockaddr_in source, dest;
int header_length = 16; //DLT_LINUX_SLL
uint8_t demmyipv6buf[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool sendFlag = false;
uint32_t currct_time_t = 0;

#define DATA_SIZE       8192

//string uniqueStringFromIpv4(char ipsrc[], char ipdest[],string srtport,string dstport,string flag) {
//
//    return string(ipsrc) + ipdest + srtport + dstport + flag;
//
//}
//
//string uniqueStringFromIpv6(const char ipsrc[], const char ipdest[],string srtport,string dstport,string flag) {
//
//    return string(ipsrc) + ipdest + srtport + dstport + flag;
//
//}

//void snifferentrypoint(int a) :
//dest_(a) {
//        // TODO Auto-generated destructor stub
//
//        std::thread t([this]() {
//            flow_timer_thread();
//        });
//        // Lambda function capturing 'this'
//        t.detach(); // Detach the thread (or join it depending on your requirements)
//
//        v9data.V9Datahedder();
//
//}

void  flow_timer_thread() {

    while (true) {
        gettimeofday(&flow_time_finder, NULL);

        //		printf("flow_time_finder ----> %d\n",flow_time_finder);
        sleep(1);
    }

}
char* inet_ntoa64(struct in_addr ina) {
    static char buf[4 * sizeof("123")];
    unsigned char *ucp = (unsigned char*) &ina;

    sprintf(buf, "%d.%d.%d.%d", ucp[0] & 0xff, ucp[1] & 0xff, ucp[2] & 0xff,
            ucp[3] & 0xff);
    return buf;
}

uint32_t getTime() {

    return 0;

    // Get the current time point in seconds since epoch
//    auto currentTime = std::chrono::system_clock::now();
//
//    // Convert the time point to time_t (seconds since epoch)
//    std::time_t timeSinceEpoch = std::chrono::system_clock::to_time_t(
//            currentTime);
//
//    // Convert time_t to a 32-bit integer (if necessary)
//    return static_cast<uint32_t>(timeSinceEpoch);

}
static const char *ether_type_name(uint16_t ethertype) {
    switch (ethertype) {
        case ETHERTYPE_IP:   return "IPv4";
        case ETHERTYPE_IPV6: return "IPv6";
        case ETHERTYPE_ARP:  return "ARP";
        default:             return "Other";
    }
}

void print_mac(const uint8_t *mac) {
    log_d(" netflow:  %02x:%02x:%02x:%02x:%02x:%02x",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}


void print_ip_header(unsigned char* Buffer, int Size)
{
    unsigned short iphdrlen;

    const struct ether_header *eth = (const struct ether_header *)Buffer;


    log_d("hex_val: *************");

//    uint16_t ethertype = ntohs(eth->ether_type);

    char *pkt_buf = (char *)Buffer; /* needed to set the zdtun_pkt_t pointers */
    uint8_t ipver = (*pkt_buf) >> 4;

    log_d("netflow EtherType: 0x%04x (%s)\n", ipver, ether_type_name(ipver));
//
//    for(int q=1;q<50;q++){
//        log_d("netflow hex_val: %x", Buffer[q]);
//
//    }
    print_mac(eth->ether_shost);
    print_mac(eth->ether_dhost);
    struct iphdr *iph = (struct iphdr *)Buffer;
    iphdrlen =iph->ihl*4;

    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;

    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;

    log_d("\n");
    log_d("IP Header\n");
    log_d("netflow   |-IP Version        : %d\n",(unsigned int)iph->version);
    log_d("netflow   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    log_d("netflow   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    log_d("netflow   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    log_d("netflow   |-Identification    : %d\n",ntohs(iph->id));
    //fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    log_d("netflow   |-TTL      : %d\n",(unsigned int)iph->ttl);
    log_d("netflow   |-Protocol : %d\n",(unsigned int)iph->protocol);
    log_d("netflow   |-Checksum : %d\n",ntohs(iph->check));
    log_d("netflow   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    log_d("netflow   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
}



int sniff_packet_proc( uint8_t *ptr,  zdtun_pkt_t *pkt, size_t len)
{

    flowstructur_s  PktBket = {0};


    char *pkt_buf = (char *)ptr; /* needed to set the zdtun_pkt_t pointers */
    uint8_t ipver = (*pkt_buf) >> 4;

    if((ipver != 4) && (ipver != 6)) {
        debug("netflow Ignoring non IP packet (len: %d, v: %d)", pkt_len, ipver);
        return -1;
        }


    if(ipver == 4)  {


        if (pkt->tuple.dst_port == 2055) {
            debug("netflow Ignoring non 2055 (len: %d)", pkt->tuple.dst_port);

            return -1;
        }
        PktBket.in_bytes += pkt->len;

        PktBket.ipv4_src_addr = ntohl( pkt->tuple.src_ip.ip4); // @suppress("Field cannot be resolved")
        PktBket.ipv4_dst_addr = ntohl( pkt->tuple.dst_ip.ip4);
        PktBket.ip6_src_addr  = (uint8_t*)&demmyipv6buf;
        PktBket.ip6_dst_addr  = (uint8_t*)&demmyipv6buf;
        PktBket.l4_src_port   =  pkt->tuple.src_port;
        PktBket.l4_dst_port   =  pkt->tuple.dst_port;

        PktBket.protocol      = pkt->tuple.ipproto;

        PktBket.in_bytes     += pkt->len;
        PktBket.in_pkts      += 1;


        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = PktBket.ipv4_src_addr;

        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = PktBket.ipv4_dst_addr;

//        log_d("netflow   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
//        log_d("netflow   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
//        log_d("netflow Ignoring 2055 (port: %d)", pkt->tuple.dst_port);

//
//        if (pkt->tuple.ipproto == IPPROTO_TCP) {
//
//            log_d("netflow   |-IPPROTO_TCP");
//
//
//        } else if(pkt->tuple.ipproto == IPPROTO_UDP) {
//            log_d("netflow   |-IPPROTO_UDP");
//
//
//        } else if(pkt->tuple.ipproto == IPPROTO_ICMP) {
//            log_d("netflow   |- IPPROTO_ICMP");
//
//        }
    } else {  //0x86DD



        currct_time_t = getTime();
        PktBket.last_switch  = currct_time_t;
        PktBket.ipv4_src_addr = ntohl(0); // @suppress("Field cannot be resolved")
        PktBket.ipv4_dst_addr = ntohl(0);
        PktBket.ip6_src_addr = (uint8_t *)&pkt->tuple.src_ip.ip6;
        PktBket.ip6_dst_addr = (uint8_t *)&pkt->tuple.dst_ip.ip6;
        PktBket.l4_src_port   =  pkt->tuple.src_port;
        PktBket.l4_dst_port   =  pkt->tuple.dst_port;

        PktBket.protocol     = pkt->tuple.ipproto;
        PktBket.in_bytes    += pkt->len;
        PktBket.in_pkts     += 1;

//
//        if (pkt->tuple.ipproto == IPPROTO_TCP) {
//            log_d("netflow   |- IPPROTO_TCP v6");
//
//
//        } else if (pkt->tuple.ipproto == IPPROTO_UDP) {
//            log_d("netflow   |- IPPROTO_UDP v6");
//
//
//        } else if(pkt->tuple.ipproto == IPPROTO_ICMP) {
//            log_d("netflow   |- IPPROTO_ICMP v6");
//
//
//        }


    }
    if(PktBket.in_pkts > 0){
        V9DataGen(&PktBket, 0);
    }


    return true;
}




bool sniff_packet_verbose( uint8_t *ptr, size_t len)
{

    log_d("netflow sniff_packet_verbose");
    struct ether_header eh;
//    struct ether_arp ether_arp;
    flowstructur_s  PktBket = {0};
    struct ip ip;
    struct ip6_hdr ip6_hdr;
    struct tcphdr tcphdr;
    struct udphdr udphdr;
    struct icmp icmp;
    uint8_t  *hptr;
    int size;
    int lest;
    uint16_t l4_src_port_ = 0;
    uint16_t l4_dst_port_ = 0;
    uint8_t tcp_flag = 0;


    (void) memcpy(&eh, ptr, ETHER_HEADER_LEN/*sizeof(struct ether_header)*/);
    ptr += ETHER_HEADER_LEN; // sizeof(struct ether_header);
    len -= ETHER_HEADER_LEN; // sizeof(struct ether_header);
//    if (ntohs(eh.ether_type) == ETHERTYPE_ARP
//        || ntohs(eh.ether_type) == ETHERTYPE_REVARP) {
//        (void) memcpy(&ether_arp, ptr,ETHER_ARP_HDR_LEN /*sizeof(struct ether_arp)*/);
//        //		printf("[ARP]\n");
//        parse_ether_header(&eh,&umapPktStor["arp"]); // @suppress("Invalid arguments")
//        //parse_ether_arp(&ether_arp);
//        //		printf("\n");
//    } else


    char *pkt_buf = (char *)ptr; /* needed to set the zdtun_pkt_t pointers */
    uint8_t ipver = (*pkt_buf) >> 4;

    if((ipver != 4) && (ipver != 6)) {
        debug("netflow Ignoring non IP packet (len: %d, v: %d)", pkt_len, ipver);
        return -1;
    }

    if (ipver == 4) {

        log_d("netflow ETHERTYPE_IP");

        print_ip_header(ptr,len);

        (void) memcpy(&ip, ptr, IPHDR_LEN/*sizeof(struct ip)*/);

        struct iphdr *tempiph = (struct iphdr*)&ip;  // beacse not able to asing to 32 bit

        if(!parse_ip(&ip)) return false;  // ignore if the is adedd in to the black list array

        ptr += IPHDR_LEN; // sizeof(struct ip);
        len = ntohs(ip.ip_len) - IPHDR_LEN; // sizeof(struct ip); // @suppress("Invalid arguments")


        PktBket.in_pkts += 1;

        if (ip.ip_p == IPPROTO_TCP) {
            (void) memcpy(&tcphdr, ptr, TCPHDR_LEN /*sizeof(struct tcphdr)*/);

            parse_tcphdr_port_flag(&tcphdr,&tcp_flag,&l4_src_port_,&l4_dst_port_);


        }
        else if(ip.ip_p == IPPROTO_UDP){
            (void) memcpy(&udphdr, ptr,UDPHDR_LEN /*sizeof(struct udphdr)*/);
            l4_src_port_ = udphdr.source;
            l4_dst_port_ = udphdr.dest;


            //			printf("udp port : %d\n",udphdr.dest);

        }
        else if(ip.ip_p == IPPROTO_ICMP){

            hptr = ptr;
            size = len;

            (void) memcpy(&icmp, ptr, ICMPHDR_LEN/*sizeof(struct icmp)*/);
            parse_icmp_get_ports(&icmp,&l4_src_port_,&l4_dst_port_,hptr,size);



        }
//
//        if (PktBket.keysToErase){
//            PktBket.keysToErase = false;
//            PktBket.first_switch = 0;
//            PktBket.in_bytes = 0;
//            PktBket.in_pkts = 0;
//            //			if (umapPktStor.erase(iphash) == 1)
//            //				std::cout << "Element Deleted key: "<<iphash<< std::endl;
//
//        }


        currct_time_t = getTime();
        PktBket.last_switch = currct_time_t;
        //		printf("111 first_switch: --: %d\n",PktBket.first_switch);
        if (!PktBket.first_switch){

            PktBket.first_switch = currct_time_t;
            PktBket.ipv4_src_addr = ntohl(tempiph->saddr); // @suppress("Field cannot be resolved")
            PktBket.ipv4_dst_addr = ntohl(tempiph->daddr);
            PktBket.ip6_src_addr  = (uint8_t*)&demmyipv6buf;
            PktBket.ip6_dst_addr  = (uint8_t*)&demmyipv6buf;
            PktBket.protocol = ip.ip_p;



        }

        if (ip.ip_p == IPPROTO_TCP) {
            PktBket.in_bytes += len;

            ptr += TCPHDR_LEN; //sizeof(struct tcphdr);
            len -= TCPHDR_LEN; //sizeof(struct tcphdr);
            parse_ether_header(&eh,&PktBket);

            parse_tcphdr(&tcphdr, &PktBket);

            lest = tcphdr.doff * 4 - TCPHDR_LEN; //sizeof(struct tcphdr);
            if (lest > 0) {
                parse_tcp_optpad(ptr, lest);
            }
            ptr += lest;
            len -= lest;
            //			if (len > 0) {
            //				parse_data(ptr, len);
            //			}


        } else if(ip.ip_p == IPPROTO_UDP) {
            PktBket.in_bytes += len;

            ptr += UDPHDR_LEN; // sizeof(struct udphdr);
            len -= UDPHDR_LEN; // sizeof(struct udphdr);

            //			 printf("in_bytes -== %d\n",PktBket.in_bytes);


            parse_ether_header(&eh,&PktBket);
            //			parse_ip(&ip);
            parse_udphdr(&udphdr,&PktBket);


        } else if(ip.ip_p == IPPROTO_ICMP) {
            PktBket.in_bytes += len;

            hptr = ptr;
            size = len;
            ptr += ICMPHDR_LEN;// sizeof(struct icmp);
            len -= ICMPHDR_LEN; //sizeof(struct icmp);

            parse_ether_header(&eh,&PktBket);
            parse_icmp(&icmp, &PktBket, hptr, size);

        }
    } else {  //0x86DD
        log_d("netflow ETHERTYPE_IPV6");

        (void) memcpy(&ip6_hdr, ptr, IP6_HDR_LEN/*sizeof(struct ip6_hdr)*/);
        ptr += IP6_HDR_LEN; // sizeof(struct ip6_hdr);
        len -= IP6_HDR_LEN; // sizeof(struct ip6_hdr);

        char buf[SIZE_OF_IPV6_BUF];

        if (ip6_hdr.ip6_nxt == IPPROTO_TCP) {

            (void) memcpy(&tcphdr, ptr,TCPHDR_LEN /*sizeof(struct tcphdr)*/);
            parse_tcphdr_port_flag(&tcphdr,&tcp_flag,&l4_src_port_,&l4_dst_port_);

        }
        else if(ip6_hdr.ip6_nxt == IPPROTO_UDP){

            (void) memcpy(&udphdr, ptr, UDPHDR_LEN /*sizeof(struct udphdr)*/);
            l4_src_port_ = udphdr.source;
            l4_dst_port_ = udphdr.dest;



        }
        else if(ip6_hdr.ip6_nxt == IPPROTO_ICMP){


            hptr = ptr;
            size = len;
            (void) memcpy(&icmp, ptr, ICMPHDR_LEN/*sizeof(struct icmp)*/);
            parse_icmp_get_ports(&icmp,&l4_src_port_,&l4_dst_port_,hptr,size);

        }


        if (PktBket.keysToErase){
            PktBket.keysToErase  = false;
            PktBket.first_switch = 0;
            PktBket.in_bytes     = 0;
            PktBket.in_pkts 	 = 0;

        }


        currct_time_t = getTime();
        PktBket.last_switch = currct_time_t;
        //		printf("111 first_switch: --: %d\n",PktBket.first_switch);
        if (!PktBket.first_switch){
            PktBket.first_switch = currct_time_t;

            PktBket.ip6_src_addr = (uint8_t *)&ip6_hdr.ip6_src;
            PktBket.ip6_dst_addr = (uint8_t *)&ip6_hdr.ip6_dst;
            PktBket.protocol = ip.ip_p;

        }




        if (ip6_hdr.ip6_nxt == IPPROTO_TCP) {

            PktBket.in_bytes += len;  //full lenth


            ptr += TCPHDR_LEN; // sizeof(struct tcphdr);
            len -= TCPHDR_LEN; // sizeof(struct tcphdr);
            //			printf("[TCP6]\n");
            parse_ether_header(&eh,&PktBket);
            //parse_ipv6(&ip6_hdr);
            parse_tcphdr(&tcphdr,&PktBket);

            lest = tcphdr.doff * 4 - TCPHDR_LEN; //sizeof(struct tcphdr);
            // if (lest > 0) {
            // 	parse_tcp_optpad(ptr, lest);
            // }
            ptr += lest;
            len -= lest;

            PktBket.in_pkts  += 1;
            // printf("len -== %ld\n",len);
            // printf("in_bytes -== %d\n",PktBket.in_bytes);

        } else if (ip6_hdr.ip6_nxt == IPPROTO_UDP) {
            PktBket.in_bytes += len;

            ptr += UDPHDR_LEN; //sizeof(struct udphdr);
            len -= UDPHDR_LEN; //sizeof(struct udphdr);

            parse_ether_header(&eh,&PktBket);
            // parse_ipv6(&ip6_hdr);
            parse_udphdr(&udphdr,&PktBket);

            PktBket.in_bytes += len;
            PktBket.in_pkts  += 1;

            // printf("len -== %ld\n",len);
            // printf("in_bytes -== %d\n",PktBket.in_bytes);

            // printf("\n");

        } else if(ip.ip_p == IPPROTO_ICMP) {

            PktBket.in_bytes += len;  //full lenth

            hptr = ptr;
            size = len;
            ptr += ICMPHDR_LEN; //sizeof(struct icmp);
            len -= ICMPHDR_LEN;  //sizeof(struct icmp);
            parse_ether_header(&eh,&PktBket);
            parse_icmp(&icmp, &PktBket, hptr, size);
            PktBket.in_pkts  += 1;

        }


    }
//    if(PktBket.in_pkts > 0){
        sendFlag = true;
        V9DataGen(&PktBket, 0);
//    }



    return true;
}
