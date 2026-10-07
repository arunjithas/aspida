
#ifndef SRC_DATAEXTRACTIONFUNCTIONS_H_
#define SRC_DATAEXTRACTIONFUNCTIONS_H_

#include "datastructur.h"

const char *netflow_header(uint8_t d[],uint16_t version,uint16_t count,uint32_t sysUpTime,uint32_t TimeStamp,uint32_t flowsequence,uint32_t sorceid,uint16_t *array_size_out);
const char *netflow_header_timeadder(uint8_t d[],uint32_t sysUpTime,uint32_t TimeStamp,uint32_t flowsequence);

const char *NULL_fun(uint8_t d[],flowstructur_s *pack, int b);
const char *byte(uint8_t d[],flowstructur_s *pack, int b);
const char *pkts(uint8_t d[],flowstructur_s *pack, int b);
const char *flows(uint8_t d[],flowstructur_s *pack, int b);
const char *protocol(uint8_t d[],flowstructur_s *pack, int b);
const char *src_tos(uint8_t d[],flowstructur_s *pack, int b);
const char *tcp_flags(uint8_t d[],flowstructur_s *pack, int b);
const char *l4_src_port(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv4_src_addr(uint8_t d[],flowstructur_s *pack, int b);
const char *src_mask(uint8_t d[],flowstructur_s *pack, int b);
const char *input_snmp(uint8_t d[],flowstructur_s *pack, int b);
const char *l4_dst_port(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv4_dst_addr(uint8_t d[],flowstructur_s *pack, int b);
const char *dst_mask(uint8_t d[],flowstructur_s *pack, int b);
const char *output_snmp(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv4_next_hop(uint8_t d[],flowstructur_s *pack, int b);
const char *src_as(uint8_t d[],flowstructur_s *pack, int b);
const char *dst_as(uint8_t d[],flowstructur_s *pack, int b);
const char *bgp_ipv4_next_hop(uint8_t d[],flowstructur_s *pack, int b);
const char *mul_dst_pkts(uint8_t d[],flowstructur_s *pack, int b);
const char *mul_dst_bytes(uint8_t d[],flowstructur_s *pack, int b);
const char *last_switched(uint8_t d[],flowstructur_s *pack, int b);
const char *first_switched(uint8_t d[],flowstructur_s *pack, int b);
const char *out_bytes(uint8_t d[],flowstructur_s *pack, int b);
const char *out_pkts(uint8_t d[],flowstructur_s *pack, int b);
const char *min_pkt_length(uint8_t d[],flowstructur_s *pack, int b);
const char *max_pkt_length(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_src_addr(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_dst_addr(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_src_mask(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_dst_mask(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_flow_label(uint8_t d[],flowstructur_s *pack, int b);
const char *icmp_type(uint8_t d[],flowstructur_s *pack, int b);
const char *mul_igmp_type(uint8_t d[],flowstructur_s *pack, int b);
const char *sampling_interval(uint8_t d[],flowstructur_s *pack, int b);
const char *sampleing_algorithm(uint8_t d[],flowstructur_s *pack, int b);
const char *flow_actuve_timeout(uint8_t d[],flowstructur_s *pack, int b);
const char *flow_inactive_timeout(uint8_t d[],flowstructur_s *pack, int b);
const char *engine_type(uint8_t d[],flowstructur_s *pack, int b);
const char *engine_id(uint8_t d[],flowstructur_s *pack, int b);
const char *total_bytes_exp(uint8_t d[],flowstructur_s *pack, int b);
const char *total_pkts_exp(uint8_t d[],flowstructur_s *pack, int b);
const char *total_flow_exp(uint8_t d[],flowstructur_s *pack, int b);
const char *vendor_proprietary(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv4_src_prefix(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv4_dst_prefix(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_top_label_type(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_top_lable_ip_addr(uint8_t d[],flowstructur_s *pack, int b);
const char *flow_sampler_id(uint8_t d[],flowstructur_s *pack, int b);
const char *flow_sampler_mode(uint8_t d[],flowstructur_s *pack, int b);
const char *flow_sampler_random_interval(uint8_t d[],flowstructur_s *pack, int b);

/*************vendor propritary****************/


const char *min_ttl(uint8_t d[],flowstructur_s *pack, int b);
const char *max_ttl(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv4_ident(uint8_t d[],flowstructur_s *pack, int b);
const char *dst_tos(uint8_t d[],flowstructur_s *pack, int b);
const char *in_src_mac(uint8_t d[],flowstructur_s *pack, int b);
const char *out_dst_mac(uint8_t d[],flowstructur_s *pack, int b);
const char *src_vlan(uint8_t d[],flowstructur_s *pack, int b);
const char *dst_vlan(uint8_t d[],flowstructur_s *pack, int b);
const char *ip_protocol_version(uint8_t d[],flowstructur_s *pack, int b);
const char *direction(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_next_hop(uint8_t d[],flowstructur_s *pack, int b);
const char *bpg_ipv6_next_hop(uint8_t d[],flowstructur_s *pack, int b);
const char *ipv6_option_headers(uint8_t d[],flowstructur_s *pack, int b);
/*************vendor propritary****************/
/*************vendor propritary****************/
/*************vendor propritary****************/
/*************vendor propritary****************/
/*************vendor propritary****************/

const char *mpls_label_1(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_2(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_3(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_4(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_5(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_6(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_7(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_8(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_9(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_label_10(uint8_t d[],flowstructur_s *pack, int b);
const char *in_dst_mac(uint8_t d[],flowstructur_s *pack, int b);
const char *out_src_mac(uint8_t d[],flowstructur_s *pack, int b);
const char *if_name(uint8_t d[],flowstructur_s *pack, int b);
const char *if_desc(uint8_t d[],flowstructur_s *pack, int b);
const char *sampler_name(uint8_t d[],flowstructur_s *pack, int b);
const char *in_permanent_bytes(uint8_t d[],flowstructur_s *pack, int b);
const char *in_permanent_pkt(uint8_t d[],flowstructur_s *pack, int b);
/*************vendor propritary****************/

const char *fragment_offset(uint8_t d[],flowstructur_s *pack, int b);
const char *forwarding_status(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_pal_rd(uint8_t d[],flowstructur_s *pack, int b);
const char *mpls_prefix_len(uint8_t d[],flowstructur_s *pack, int b);
const char *src_traffic_index(uint8_t d[],flowstructur_s *pack, int b);
const char *dst_traffic_index(uint8_t d[],flowstructur_s *pack, int b);
const char *application_description(uint8_t d[],flowstructur_s *pack, int b);
const char *application_tag(uint8_t d[],flowstructur_s *pack, int b);
const char *application_name(uint8_t d[],flowstructur_s *pack, int b);
const char *postipDiffServCodePoint(uint8_t d[],flowstructur_s *pack, int b);
const char *replication_factor(uint8_t d[],flowstructur_s *pack, int b);
const char *desprecated(uint8_t d[],flowstructur_s *pack, int b);
const char *layer2packetSectionOffset(uint8_t d[],flowstructur_s *pack, int b);
const char *layer2packetSectionSize(uint8_t d[],flowstructur_s *pack, int b);
const char *layer2packetSectionData(uint8_t d[],flowstructur_s *pack, int b);
const char *lastrange_for_user(uint8_t d[],flowstructur_s *pack, int b);


const char * netflow_temp_function_serch(uint32_t template_elament,uint8_t   *converted_data,flowstructur_s *pack,int b);



#endif /* SRC_DATAEXTRACTIONFUNCTIONS_H_ */
