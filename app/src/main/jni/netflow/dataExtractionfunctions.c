
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <arpa/inet.h>

#include "dataExtractionfunctions.h"


const char *(*fun_ptr_arr[])(uint8_t [],flowstructur_s *, int) = {  NULL_fun,

                                                                    byte,         		pkts,          		flows,         			protocol,
                                                                    src_tos,       		tcp_flags,     		l4_src_port,   			ipv4_src_addr,
                                                                    src_mask,      		input_snmp,    		l4_dst_port,   			ipv4_dst_addr,
                                                                    dst_mask,      		output_snmp,   		ipv4_next_hop, 			src_as,
                                                                    dst_as,        		        		bgp_ipv4_next_hop,		mul_dst_pkts,
                                                                    mul_dst_bytes, 		last_switched, 		first_switched, 		out_bytes,
                                                                    out_pkts,     		min_pkt_length, 	max_pkt_length, 		ipv6_src_addr,
                                                                    ipv6_dst_addr, 		ipv6_src_mask, 		ipv6_dst_mask, 			ipv6_flow_label,
                                                                    icmp_type,   		mul_igmp_type,		sampling_interval, 		sampleing_algorithm,
                                                                    flow_actuve_timeout,	flow_inactive_timeout, 	engine_type,			engine_id,
                                                                    total_bytes_exp,	total_pkts_exp,		total_flow_exp,			vendor_proprietary,
                                                                    ipv4_src_prefix,	ipv4_dst_prefix,	mpls_top_label_type,		mpls_top_lable_ip_addr,
                                                                    flow_sampler_id,	flow_sampler_mode,	flow_sampler_random_interval,	NULL_fun,
                                                                    min_ttl,		max_ttl,		ipv4_ident,			dst_tos,
                                                                    in_src_mac,		out_dst_mac,		src_vlan,			dst_vlan,
                                                                    ip_protocol_version,	direction,		ipv6_next_hop,			bpg_ipv6_next_hop,
                                                                    ipv6_option_headers,	NULL_fun,		NULL_fun,			NULL_fun,
                                                                    NULL_fun,		NULL_fun,		mpls_label_1,			mpls_label_2,
                                                                    mpls_label_3,		mpls_label_4,		mpls_label_5,			mpls_label_6,
                                                                    mpls_label_7,		mpls_label_8,		mpls_label_9,			mpls_label_10,
                                                                    in_dst_mac,		out_src_mac,		if_name,			if_desc,
                                                                    sampler_name,		in_permanent_bytes,	in_permanent_pkt,		NULL_fun,
                                                                    fragment_offset,	forwarding_status,	mpls_pal_rd,			mpls_prefix_len,
                                                                    src_traffic_index,	dst_traffic_index,	application_description,	application_tag,
                                                                    application_name,	postipDiffServCodePoint,replication_factor,		desprecated,
                                                                    layer2packetSectionOffset,layer2packetSectionSize,layer2packetSectionData,	lastrange_for_user


};


const char * netflow_temp_function_serch(uint32_t template_elament,uint8_t   *converted_data,flowstructur_s *pack,int b){
    return ((*fun_ptr_arr[template_elament])(converted_data,pack, b));
}


const char *netflow_header(uint8_t d[],uint16_t version,uint16_t count,uint32_t sysUpTime,uint32_t TimeStamp,uint32_t flowsequence,uint32_t sorceid,uint16_t *array_size_out){


    d[0] = version;
    d[1] = version >> 8;

    d[2] = count;
    d[3] = count >> 8;

    d[4] = sysUpTime;
    d[5] = sysUpTime >> 8;
    d[6] = sysUpTime >> 16;
    d[7] = sysUpTime >> 24;

    d[8] = TimeStamp;
    d[9] = TimeStamp >> 8;
    d[10] = TimeStamp >> 16;
    d[11] = TimeStamp >> 24;

    d[12] = flowsequence;
    d[13] = flowsequence >> 8;
    d[14] = flowsequence >> 16;
    d[15] = flowsequence >> 24;

    d[16] = sorceid;
    d[17] = sorceid >> 8;
    d[18] = sorceid >> 16;
    d[19] = sorceid >> 24;

    *array_size_out = 20;

    return " header version/count/sysUpTime/TimeStamp/flowsequence/sorceid";

}

const char *netflow_header_timeadder(uint8_t d[],uint32_t sysUpTime,uint32_t TimeStamp,uint32_t flowsequence){
    d[4] = sysUpTime;
    d[5] = sysUpTime >> 8;
    d[6] = sysUpTime >> 16;
    d[7] = sysUpTime >> 24;

    d[8] = TimeStamp;
    d[9] = TimeStamp >> 8;
    d[10] = TimeStamp >> 16;
    d[11] = TimeStamp >> 24;
    return "netflow_header_timeadder";
}

const char *NULL_fun(uint8_t d[],flowstructur_s *pack, int b){d[0]='0';return "NULL_fun";}

const char *byte(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data="byte 1";
    //	uint32_t i = 654789;
    uint32_t in = htonl((uint32_t)pack->in_bytes);

    d[0] = in;
    d[1] = in >> 8;
    d[2] = in >> 16;
    d[3] = in >> 24;

    return data;
}

const char *pkts(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "pkts 2";

    uint32_t in = htonl((uint32_t)pack->in_pkts);

    d[0] = in;
    d[1] = in >> 8;
    d[2] = in >> 16;
    d[3] = in >> 24;

    return data;
}

const char *flows(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "flows 3";

    return data;
}

const char *protocol(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "protocol 4";

    //	d[0] = 16;
    d[0] = pack->protocol;

    return data;
}

const char *src_tos(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "src_tos 6";

    d[0] = 22;

    return data;
}

const char *tcp_flags(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "tcp_flags";

    d[0] = pack->tcp_flags;

    return data;
}

const char *l4_src_port(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data ="l4_src_port 7";
    //	uint16_t port = htons(5025);

    uint16_t port = pack->l4_src_port;

    d[0] = port;
    d[1] = port >> 8;

    return data;
}

const char *ipv4_src_addr(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data="ipv4_src_addr 8";

    //	uint32_t ip = htonl(169739308);
    uint32_t ip = htonl((uint32_t)pack->ipv4_src_addr);

    d[0] = ip;
    d[1] = ip >> 8;
    d[2] = ip >> 16;
    d[3] = ip >> 24;
    return data;
}

const char *src_mask(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *input_snmp(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "input_snmp 10";

    uint16_t in = htons(5025);
    d[0] = in;
    d[1] = in>>8;

    return data;
}

const char *l4_dst_port(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "l4_dst_port 11";

    //	uint16_t port = htons(2222);
    uint16_t port = pack->l4_dst_port;

    d[0]=port;
    d[1]=port>>8;

    return data;
}

const char *ipv4_dst_addr(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "ipv4_dst_addr 12 ";

    //	uint32_t ip = htonl(169739309);
    uint32_t ip = htonl((uint32_t)pack->ipv4_dst_addr);


    d[0] = ip;
    d[1] = ip >> 8;
    d[2] = ip >> 16;
    d[3] = ip >> 24;
    return data;
}

const char *dst_mask(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *output_snmp(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "output_snmp 14";

    uint16_t in = htons(6565);

    d[0] = in;
    d[1] = in >>8;

    return data;
}

const char *ipv4_next_hop(uint8_t d[],flowstructur_s *pack, int b)
{

    const char *data="ipv4_next_hop";

    uint32_t ip = htonl(169739296);

    d[0] = ip;
    d[1] = ip >> 8;
    d[2] = ip >> 16;
    d[3] = ip >> 24;
    return data;


}

const char *src_as(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *dst_as(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *bgp_ipv4_next_hop(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *mul_dst_pkts(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *mul_dst_bytes(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *last_switched(uint8_t d[],flowstructur_s *pack, int b)
{

    const char *data="last_switched 21";

    uint32_t in = htonl((uint32_t)pack->last_switch);
//
    d[0] = in;
    d[1] = in >> 8;
    d[2] = in >> 16;
    d[3] = in >> 24;


//	d[0] = pack->last_switch;
//	d[1] = pack->last_switch >> 8;
//	d[2] = pack->last_switch >> 16;
//	d[3] = pack->last_switch >> 24;


    return data;
}

const char *first_switched(uint8_t d[],flowstructur_s *pack, int b)
{

    const char *data="first_switched 22";

    uint32_t in = htonl((uint32_t)pack->first_switch);

//	uint32_t in = (uint32_t)pack->first_switch;


    d[0] = in;
    d[1] = in >> 8;
    d[2] = in >> 16;
    d[3] = in >> 24;

//	d[0] = pack->first_switch;
//	d[1] = pack->first_switch >> 8;
//	d[2] = pack->first_switch >> 16;
//	d[3] = pack->first_switch >> 24;


    return data;
}

const char *out_bytes(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *out_pkts(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *min_pkt_length(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *max_pkt_length(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *ipv6_src_addr(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "ipv6_src_addr";
    //	printf("ip6 src -> %d\n",pack->ip6_src_addr[0]);
    //	for (int i=0;i<16;i++)
    //		printf("%x",pack->ip6_src_addr[i]);
    //	printf("\n");
    //	if(!pack->ip6_src_addr)
    //	d[0] =
    memcpy(d, pack->ip6_src_addr, 16);
    return data;
}

const char *ipv6_dst_addr(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "ipv6_dst_addr";
    //	for (int i=0;i<17;i++)
    //		printf("%x",pack->ip6_dst_addr[i]);
    //	printf("\n");
    //	if(!pack->ip6_dst_addr)
    memcpy(d, pack->ip6_dst_addr, 16);

    return data;
}

const char *ipv6_src_mask(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *ipv6_dst_mask(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *ipv6_flow_label(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *icmp_type(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    uint16_t in = htonl((uint32_t)pack->icmp_type);

    d[0] = in;
    d[1] = in >> 8;
    return data;
}

const char *mul_igmp_type(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *sampling_interval(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *sampleing_algorithm(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *flow_actuve_timeout(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *flow_inactive_timeout(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *engine_type(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *engine_id(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *total_bytes_exp(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *total_pkts_exp(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *total_flow_exp(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *vendor_proprietary(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *ipv4_src_prefix(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *ipv4_dst_prefix(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_top_label_type(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_top_lable_ip_addr(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *flow_sampler_id(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *flow_sampler_mode(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *flow_sampler_random_interval(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}


/*************vendor propritary****************/




const char *min_ttl(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *max_ttl(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *ipv4_ident(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *dst_tos(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *in_src_mac(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "in_src_mac";
    d[0] = pack->in_src_mac[0];
    d[1] = pack->in_src_mac[1];
    d[2] = pack->in_src_mac[2];
    d[3] = pack->in_src_mac[3];
    d[4] = pack->in_src_mac[4];
    d[5] = pack->in_src_mac[5];
    return data;
}
const char *out_dst_mac(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "out_dst_mac";
    d[0] = pack->out_dst_mac[0];
    d[1] = pack->out_dst_mac[1];
    d[2] = pack->out_dst_mac[2];
    d[3] = pack->out_dst_mac[3];
    d[4] = pack->out_dst_mac[4];
    d[5] = pack->out_dst_mac[5];

    return data;
}
const char *src_vlan(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *dst_vlan(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *ip_protocol_version(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    d[0]=pack->protocol;

    return data;
}
const char *direction(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *ipv6_next_hop(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *bpg_ipv6_next_hop(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *ipv6_option_headers(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
/*************vendor propritary****************/
/*************vendor propritary****************/
/*************vendor propritary****************/
/*************vendor propritary****************/
/*************vendor propritary****************/


const char *mpls_label_1(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_2(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_3(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_4(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_5(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_6(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_7(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_8(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_9(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *mpls_label_10(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *in_dst_mac(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *out_src_mac(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *if_name(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *if_desc(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *sampler_name(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *in_permanent_bytes(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}
const char *in_permanent_pkt(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

/*************vendor propritary****************/



const char *fragment_offset(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *forwarding_status(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *mpls_pal_rd(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *mpls_prefix_len(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *src_traffic_index(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *dst_traffic_index(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *application_description(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *application_tag(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *application_name(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *postipDiffServCodePoint(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *replication_factor(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *desprecated(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *layer2packetSectionOffset(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *layer2packetSectionSize(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *layer2packetSectionData(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}

const char *lastrange_for_user(uint8_t d[],flowstructur_s *pack, int b)
{
    const char *data = "";

    return data;
}




/*uint8_t *(*fun_ptr_arr[])(int, int) = {
				 src_ip,
				 dest_ip,
				 src_port,
				 dst_port
				};*/


/*int main()
{
// fun_ptr_arr is an array of function pointers

unsigned int ch, a = 15, b = 10;


scanf("%d", &ch);

if (ch > 2) return 0;



printf("----%c\n ",((*fun_ptr_arr[ch])(a, b))[0]);

return 0;
}*/
