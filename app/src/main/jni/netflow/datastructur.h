/*
 * datastructur.h
 *
 *  Created on: 24-Nov-2022
 *      Author: prithvi
 */

#ifndef INCLUDE_DATASTRUCTUR_H_
#define INCLUDE_DATASTRUCTUR_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct packethedderstruct_t{
    //#define IPv4_TYPE 2048
    //#define IPv6_TYPE 34525
    //packet type ipv4=2048 or ipv6=34525
    int packet_type;


    //	printf("Ethernet Frame: \n");
    //	printf("\t  | Source MAC: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    //	printf("    | Destination MAC: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    //	printf("    | Protocol : %d\n", eth->h_proto);
    struct ethhdr   *eth;
    struct iphdr    *iphdr_2;
    struct ip       *iphdr;
    struct ip6_hdr  *ip6hdr;


}packethedderstruct_s;


typedef struct flowstructur_t{


    bool data_lock_bool;
    bool keysToErase;
    uint32_t in_bytes;
    uint32_t in_pkts;
    uint32_t flows;
    uint8_t protocol;
    uint8_t src_tos;

    uint8_t tcp_flags;
    uint16_t l4_src_port;
    uint32_t ipv4_src_addr;
    uint8_t src_mask;


    uint16_t input_snmp;
    uint16_t l4_dst_port;
    uint32_t ipv4_dst_addr;

    uint8_t dst_mask;
    uint32_t ipv4_next_hop;

    uint16_t src_as;
    uint16_t dst_as;

    uint32_t bgp_ipv4_next_hop;
    uint32_t mul_dst_pkts;
    uint32_t mul_dst_bytes;

    uint32_t last_switch;
    uint32_t first_switch;
    uint32_t out_bytes;
    uint32_t out_pkts;

    uint16_t min_pkt_lngth;
    uint16_t max_pkt_lngth;
//	uint8_t ip6_src_addr[16];
//	uint8_t ip6_dst_addr[16];
    uint8_t *ip6_src_addr;
    uint8_t *ip6_dst_addr;

    uint8_t ipv6_src_mask;
    uint8_t ipv6_dst_mask;

    uint8_t ipv6_flow_label[3]; //IPV6_FLOW_LABEL 3 bytes

    uint16_t icmp_type;
    uint8_t mul_igmp_type;

    uint32_t sampling_interval;
    uint8_t sampling_algorithem;


    uint16_t flow_actuve_timeout ;
    uint16_t flow_inactuve_timeout;

    uint8_t engine_tupe;
    uint8_t engine_id;

    uint32_t total_bytes_exp;
    uint32_t toatl_pkts_exp;

    uint32_t total_flows_exp;

    /*Vendor Proprietary*/     //43 not declitedt


    uint32_t ipv4_src_prefix;
    uint32_t ipv4_dst_prefix;
    uint8_t mpls_top_label_type;

    uint32_t mpls_top_label_ip_addr;
    uint8_t flow_sampler_id;
    uint8_t flow_sampler_mode;
    uint32_t flow_sampler_random_interval;
    /**Vendor Proprietary**/ //51
    uint8_t min_ttl;
    uint8_t max_ttl;
    uint16_t ipv4_ident;
    uint8_t dst_tos;
    uint8_t in_src_mac[6];
    uint8_t out_dst_mac[6];

    uint16_t src_vlan;
    uint16_t dst_vlan;
    uint8_t ip_protocol_vertion;
    uint8_t direction;

    uint8_t ipv6_next_hop[16];
    uint8_t bgp_ipv6_next_hop[16];

    /*Vendor Proprietary*/ //  65
    /*Vendor Proprietary*/ // 66
    /*Vendor Proprietary*/ // 67
    /*Vendor Proprietary*/ // 68
    /*Vendor Proprietary*/ // 69

    uint8_t mpls_label_1[3];
    uint8_t mpls_label_2[3];
    uint8_t mpls_label_3[3];
    uint8_t mpls_label_4[3];
    uint8_t mpls_label_5[3];
    uint8_t mpls_label_6[3];
    uint8_t mpls_label_7[3];
    uint8_t mpls_label_8[3];
    uint8_t mpls_label_9[3];
    uint8_t mpls_label_10[3];

    uint8_t in_dst_mac[6];
    uint8_t out_src_mac[6];


    uint8_t if_name[10];  //N (default specified in template)
    uint8_t if_desc[10];  //N (default specified in template)

    uint8_t sampler_name[10];  //N (default specified in template)

    uint8_t in_permanent_bytes[4];  // N(default is 4)
    uint8_t in_permanent_pkts[4];  // N(default is 4)

    /* Vendor Proprietary*/ //87


    uint16_t fragment_offset;
    uint8_t forwarding_status;

    uint8_t mpls_pal_rd[8];
    uint8_t mpls_prefix_len;
    uint32_t src_traffic_index;
    uint32_t dst_traffic_index;

    uint8_t application_description[10]; // N
    uint8_t application_tag[10]; // 1+N  8bit of engine id

    uint8_t postipDiffServCodePoint;
    uint32_t replication_factor;

    uint8_t deprecated[10]; // N

    uint8_t layer2packetSectionOffset[10];
    uint8_t layer2packetSectionSize[10];
    uint8_t layer2packetSectionData[10];


}flowstructur_s;


#endif /* INCLUDE_DATASTRUCTUR_H_ */
