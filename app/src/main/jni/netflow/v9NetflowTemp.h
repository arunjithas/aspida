
#ifndef SRC_V9NETFLOWTEMP_H_
#define SRC_V9NETFLOWTEMP_H_


#include <stdint.h>

struct flow_ver9_hdr {
    uint16_t version;         /* Current version=5*/
    uint16_t count;           /* The number of records in PDU. */
    uint32_t sysUptime;       /* Current time in msecs since router booted */
    uint32_t unix_secs;       /* Current seconds since 0000 UTC 1970 */
    uint32_t flowsequence;
    uint32_t source_id;       /* Sequence number of total flows seen */
};

struct flow_ver9_data_hdr {
    uint16_t version;         /* Current version=5*/
    uint16_t count;           /* The number of records in PDU. */
    uint32_t sysUptime;       /* Current time in msecs since router booted */
    uint32_t unix_secs;       /* Current seconds since 0000 UTC 1970 */
    uint32_t flowsequence;
    uint32_t source_id;       /* Sequence number of total flows seen */
};

typedef struct template_record_s {

    uint16_t  	template_id;
    uint16_t  	count;
    struct {
        uint16_t  type;
        uint16_t  length;
    } record[50];
} template_record_t;

typedef struct template_flowset_s {
    uint16_t  	flowset_id;
    uint16_t  	length;
    template_record_t	fields;


}template_flowset_t;



typedef struct single_flow_ver9_template {
    struct flow_ver9_hdr flowHeader;
    struct template_flowset_s template_flowset;
}template_v9_Record;


#define MAX_UDP_DATA_SIZE (1500-50)

#define EX_MULIPLE	8
#define COMMON_BLOCK_ID 0
#define COMMON_BLOCK	0
#define EX_AGGR_FLOWS_4	18
#define EX_IO_SNMP_2	4
#define EX_IO_SNMP_4	5
#define EX_AS_2	6


#define NETFLOW_VERTION 9
#define COUNT_OF_FLOWS 1

#define Temp_264  264
#define Extra_field 4

#define NF9_DATA_FLOWSET_ID_SIZE     2
#define NF9_DATA_FLOWSET_LENTH_SIZE     2


#define _0byte    0
#define _1byte    1
#define _2bytes   2
#define _3bytes   3
#define _4bytes   4
#define _6bytes   6
#define _8bytes   8
#define _12bytes  12
#define _16bytes  16
#define _20bytes  20
#define _24bytes  24
#define _65bytes  65
#define _72bytes  72

#define NF9_TEMPLATE_FLOWSET_ID     0
#define NF9_OPTIONS_FLOWSET_ID      1
#define NF9_MIN_RECORD_FLOWSET_ID   256

// Flowset record types
#define NF9_IN_BYTES            1
#define NF9_IN_PACKETS          2
#define NF9_FLOWS_AGGR			3
#define NF9_IN_PROTOCOL         4
#define NF9_SRC_TOS         	5
#define NF9_TCP_FLAGS           6
#define NF9_L4_SRC_PORT         7
#define NF9_IPV4_SRC_ADDR       8
#define NF9_SRC_MASK			9
#define NF9_INPUT_SNMP          10

#define NF9_L4_DST_PORT         11
#define NF9_IPV4_DST_ADDR       12
#define NF9_DST_MASK			13
#define NF9_OUTPUT_SNMP         14
#define NF9_V4_NEXT_HOP			15
#define NF9_SRC_AS          	16
#define NF9_DST_AS          	17
#define NF9_BGP_V4_NEXT_HOP		18
#define NF9_MUL_DST_PKTS        19
#define NF9_MUL_DST_BYTES       20

#define NF9_LAST_SWITCHED       21
#define NF9_FIRST_SWITCHED      22
#define NF9_OUT_BYTES       	23
#define NF9_OUT_PKTS    	24
#define NF9_MIN_PKT_LNGTH       25
#define NF9_MAX_PKT_LNGTH       26
#define NF9_IPV6_SRC_ADDR       27
#define NF9_IPV6_DST_ADDR       28
#define NF9_IPV6_SRC_MASK	29
#define NF9_IPV6_DST_MASK	30

#define NF9_IPV6_FLOW_LABEL	31
#define NF9_ICMP_TYPE		32
#define NF9_MUL_IGMP_TYPE         33
#define NF9_SAMPLING_INTERVAL	  34
#define NF9_SAMPLING_ALGORITHM	  35
#define NF9_FLOW_ACTIVE_TIMEOUT   36
#define NF9_FLOW_INACTIVE_TIMEOUT 37
#define NF9_ENGINE_TYPE		38
#define NF9_ENGINE_ID		39

#define TOTAL_BYTES_EXP     40
#define TOTAL_PKTS_EXP      41
#define TOTAL_FLOWS_EXP     42

#define Vendor_Proprietary   43
#define IPV4_SRC_PREFIX      44
#define IPV4_DST_PREFIX      45
#define MPLS_TOP_LABEL_TYPE  46

#define MPLS_TOP_LABEL_IP_ADDR 47



#define FLOW_SAMPLER_ID 	48
#define FLOW_SAMPLER_MODE 	49
#define NF9_FLOW_SAMPLER_RANDOM_INTERVAL 50

#define Vendor_Proprietary_51 51

#define MIN_TTL			52
#define MAX_TTL			53
#define IPV4_IDENT		54

#define NF9_DST_TOS         	55
#define NF9_IN_SRC_MAC			56
#define NF9_OUT_DST_MAC			57
#define NF9_SRC_VLAN			58
#define NF9_DST_VLAN			59

#define IP_PROTOCOL_VERSION     60

#define NF9_DIRECTION	        61
#define NF9_V6_NEXT_HOP 		62
#define NF9_BPG_V6_NEXT_HOP   	63
#define IPV6_OPTION_HEADERS    64

#define Vendor_Proprietary_65   65
#define Vendor_Proprietary_66   66
#define Vendor_Proprietary_67   67
#define Vendor_Proprietary_68   68
#define Vendor_Proprietary_69   69


#define NF9_MPLS_LABEL_1		70
#define NF9_MPLS_LABEL_2		71
#define NF9_MPLS_LABEL_3		72
#define NF9_MPLS_LABEL_4		73
#define NF9_MPLS_LABEL_5		74
#define NF9_MPLS_LABEL_6		75
#define NF9_MPLS_LABEL_7		76
#define NF9_MPLS_LABEL_8		77
#define NF9_MPLS_LABEL_9		78
#define NF9_MPLS_LABEL_10		79
#define NF9_IN_DST_MAC			80
#define NF9_OUT_SRC_MAC			81

#define IF_NAME                 82
#define IF_DESC                 83
#define SAMPLER_NAME            84
#define IN_PERMANENT_BYTES      85
#define IN_PERMANENT_PKTS       86
#define Vendor_Proprietary_87   87
#define FRAGMENT_OFFSET         88

#define NF9_FORWARDING_STATUS	89

#define MPLS_PAL_RD             90
#define MPLS_PREFIX_LEN         91
#define SRC_TRAFFIC_INDEX       92
#define DST_TRAFFIC_INDEX       93
#define APPLICATION_DESCRIPTION 94
#define APPLICATION_TAG         95
#define APPLICATION_NAME        96
#define null_97                 97


#define postipDiffServCodePoint 98
#define replication_factor      99
#define DEPRECATED              100

#define null_101                101
#define layer2packetSectionOffset 102
#define layer2packetSectionSize  103
#define layer2packetSectionData  104





#define NF9_BGP_ADJ_NEXT_AS 	128
#define NF9_BGP_ADJ_PREV_AS 	129



// CISCO ASA NSEL extension - Network Security Event Logging
#define NF_F_FLOW_BYTES				   85
#define NF_F_CONN_ID                  148
#define NF_F_FLOW_CREATE_TIME_MSEC	  152
#define NF_F_ICMP_TYPE                176
#define NF_F_ICMP_CODE                177
#define NF_F_ICMP_TYPE_IPV6           178
#define NF_F_ICMP_CODE_IPV6           179
#define NF_F_FWD_FLOW_DELTA_BYTES	  231
#define NF_F_REV_FLOW_DELTA_BYTES	  232
#define NF_F_FW_EVENT84			  	  233
#define NF_F_EVENT_TIME_MSEC          323
#define NF_F_INGRESS_ACL_ID         33000
#define NF_F_EGRESS_ACL_ID          33001
#define NF_F_FW_EXT_EVENT           33002
#define NF_F_USERNAME               40000
#define NF_F_XLATE_SRC_ADDR_IPV4    40001
#define NF_F_XLATE_DST_ADDR_IPV4    40002
#define NF_F_XLATE_SRC_PORT         40003
#define NF_F_XLATE_DST_PORT         40004
#define NF_F_FW_EVENT               40005

// Cisco ASR 1000 series NEL extension - Nat Event Logging
#define NF_N_NAT_EVENT					230
#define NF_N_INGRESS_VRFID				234
#define NF_N_NAT_INSIDE_GLOBAL_IPV4		225
#define NF_N_NAT_OUTSIDE_GLOBAL_IPV4	226
#define NF_N_POST_NAPT_SRC_PORT			227
#define NF_N_POST_NAPT_DST_PORT			228


// nprobe latency extensions
#define NF9_NPROBE_CLIENT_NW_DELAY_SEC	57554
#define NF9_NPROBE_CLIENT_NW_DELAY_USEC	57555
#define NF9_NPROBE_SERVER_NW_DELAY_SEC	57556
#define NF9_NPROBE_SERVER_NW_DELAY_USEC 57557
#define NF9_NPROBE_APPL_LATENCY_SEC		57558
#define NF9_NPROBE_APPL_LATENCY_USEC	57559



/* module limited globals */
static struct v9_element_map_s {

    uint16_t	id;		// v9 element id
    char		*name;		// name string
    uint16_t	length;		// type of this element ( input length )
    uint16_t	out_length;	// type of this element ( output length )
    uint16_t	extension;	// maps into nfdump extension ID
} v9_element_map[] = {
        {0, 0, 0},
        // packets and bytes are always stored in 64bits
        { NF9_IN_BYTES, 			 (char*)"bytes",			_4bytes,  _8bytes,  0 },
        { NF9_IN_PACKETS, 			 (char*)"packets",			_4bytes,  _8bytes,  0 },
        { NF9_FLOWS_AGGR, 			 (char*)"flows",			_4bytes,  _4bytes,  0 },
        { NF9_IN_PROTOCOL, 		 	(char*)"proto",			_1byte,   _1byte,   0 },
        { NF9_SRC_TOS, 		 	 	(char*)"tos",				_1byte,   _1byte,   0 },
        { NF9_TCP_FLAGS, 		  	(char*)"flags",			_1byte,   _1byte,   0 },
        { NF9_L4_SRC_PORT, 		 	(char*)"src port",			_2bytes,  _2bytes,  0 },
        { NF9_IPV4_SRC_ADDR,		        (char*)"V4 src addr",			_4bytes,  _4bytes,  0 },
        { NF9_SRC_MASK, 	 		(char*)"V4 src mask",			_1byte,   _1byte ,  0 },
        { NF9_INPUT_SNMP, 			(char*)"input SNMP",			_2bytes,  _2bytes,  0 },
        { NF9_L4_DST_PORT, 		 	(char*)"dst port",			_2bytes,  _2bytes,  0 },
        { NF9_IPV4_DST_ADDR,		        (char*)"V4 dst addr",			_4bytes,  _4bytes,  0 },
        { NF9_DST_MASK, 	 		(char*)"V4 dst mask",			_1byte,   _1byte,   0 },
        { NF9_OUTPUT_SNMP, 			(char*)"output SNMP",			_2bytes,  _2bytes,  0 },
        { NF9_V4_NEXT_HOP,		 	(char*)"V4 next hop IP",		_4bytes,  _4bytes,  0 },
        { NF9_SRC_AS, 			 	(char*)"src AS",			_2bytes,  _2bytes,  0 },
        { NF9_DST_AS, 			 	(char*)"dst AS",			_2bytes,  _2bytes,  0 },
        { NF9_BGP_V4_NEXT_HOP,		        (char*)"V4 BGP next hop",		_4bytes,  _4bytes,  0 },
        { NF9_MUL_DST_PKTS, 			(char*)"mul dst pkets",		_4bytes,  _4bytes,  0 },
        { NF9_MUL_DST_BYTES, 			(char*)"mul dst bytes",		_4bytes,  _4bytes,  0 },
        { NF9_LAST_SWITCHED, 		        (char*)"last switched",		_4bytes,  _4bytes,  0 },
        { NF9_FIRST_SWITCHED, 		        (char*)"first switched",		_4bytes,  _4bytes,  0 },
        { NF9_OUT_BYTES, 			(char*)"out bytes",			_4bytes,  _8bytes,  0 },
        { NF9_OUT_PKTS, 			(char*)"out packets",			_4bytes,  _8bytes,  0 },
        { NF9_MIN_PKT_LNGTH, 			(char*)"min pkt lngth",		_2bytes,  _2bytes,  0 },
        { NF9_MAX_PKT_LNGTH, 			(char*)"max pkt lngth",		_2bytes,  _2bytes,  0 },
        { NF9_IPV6_SRC_ADDR,		        (char*)"V6 src addr",			_16bytes, _16bytes, 0 },
        { NF9_IPV6_DST_ADDR,		        (char*)"V6 dst addr",			_16bytes, _16bytes, 0 },
        { NF9_IPV6_SRC_MASK, 	 	        (char*)"V6 src mask",			_1byte,   _1byte,   0 },
        { NF9_IPV6_DST_MASK, 	 	        (char*)"V6 dst mask",			_1byte,   _1byte,   0 },
        { NF9_IPV6_FLOW_LABEL, 		        (char*)"V6 flow label",		_3bytes,  _3bytes,  0 },
        { NF9_ICMP_TYPE, 			(char*)"ICMP type",			_2bytes,  _2bytes,  0 },
        { NF9_MUL_IGMP_TYPE, 			(char*)"mul igmp type",		_1byte,   _1byte,   0 },
        { NF9_SAMPLING_INTERVAL, 	        (char*)"sampling interval",		_4bytes,  _4bytes,  0 },
        { NF9_SAMPLING_ALGORITHM,  	        (char*)"sampling algorithm",		_1byte,   _1byte,   0 },
        { NF9_FLOW_ACTIVE_TIMEOUT, 	        (char*)"flow active time out",	_4bytes,  _4bytes,  0 },
        { NF9_FLOW_INACTIVE_TIMEOUT,  	        (char*)"flow inactive time out",	_1byte,   _1byte,   0 },
        { NF9_ENGINE_TYPE,  	 	        (char*)"engine type",			_1byte,   _1byte,   0 },
        { NF9_ENGINE_ID,  	 	 	(char*)"engine ID",			_1byte,   _1byte,   0 },

        { TOTAL_BYTES_EXP,  	 	 	(char*)"total bytes exp",			_4bytes,   _4bytes,   0 },
        { TOTAL_PKTS_EXP,  	 	 	(char*)"total pkts exp",			_4bytes,   _4bytes,   0 },
        { TOTAL_FLOWS_EXP,  	 	 	(char*)"total flow exp",			_4bytes,   _4bytes,   0 },
        { Vendor_Proprietary,  	 	 	(char*)"Vendor Proprietary",			_72bytes,   _72bytes,   0 },

        { IPV4_SRC_PREFIX,  	 	 	(char*)"ipv4 src prefix",			_4bytes,   _4bytes,   0 },
        { IPV4_DST_PREFIX,  	 	 	(char*)"total dst prefix",			_4bytes,   _4bytes,   0 },
        { MPLS_TOP_LABEL_TYPE,  	 	 	(char*)"mpls top label type",			_1byte,   _1byte,   0 },
        { MPLS_TOP_LABEL_IP_ADDR,  	 	 	(char*)"mpls top label ip addr",			_4bytes,   _4bytes,   0 },



        { FLOW_SAMPLER_ID, 	 	        (char*)"sampler ID",			_1byte,   _1byte,   0 },
        { FLOW_SAMPLER_MODE, 	 	        (char*)"sampler mode",		_1byte,   _1byte,   0 },
        { NF9_FLOW_SAMPLER_RANDOM_INTERVAL,     (char*)"sampler rand interval",	_4bytes, _4bytes,   0 },

        { Vendor_Proprietary_51,  	 	 	(char*)"Vendor Proprietary 51",			_72bytes,   _72bytes,   0 },
        { MIN_TTL, 	 	        (char*)"min ttl",			_1byte,   _1byte,   0 },
        { MAX_TTL, 	 	        (char*)"max ttl",			_1byte,   _1byte,   0 },
        { IPV4_IDENT, 	 	        (char*)"ipv4  Idnt",			_2bytes,   _2bytes,   0 },


        { NF9_DST_TOS, 		 	 	(char*)"dst tos",			_1byte,   _1byte,   0 },
        { NF9_IN_SRC_MAC, 			(char*)"in src mac",			_6bytes,  _8bytes,  0 },
        { NF9_OUT_DST_MAC, 	 		(char*)"out dst mac",			_6bytes,  _8bytes,  0 },
        { NF9_SRC_VLAN, 			(char*)"src vlan",			_2bytes,  _2bytes,  0 },
        { NF9_DST_VLAN, 			(char*)"dst vlan",			_2bytes,  _2bytes,  0 },

        { IP_PROTOCOL_VERSION, 		 	 	(char*)"ip protocol version",			_1byte,   _1byte,   0 },

        { NF9_DIRECTION, 	 	 	(char*)"direction",			_1byte,   _1byte,   0 },
        { NF9_V6_NEXT_HOP,			(char*)"V6 next hop IP",		_16bytes, _16bytes, 0 },
        { NF9_BPG_V6_NEXT_HOP,	 	        (char*)"V6 BGP next hop",		_16bytes, _16bytes, 0 },


        { IPV6_OPTION_HEADERS, 	 		(char*)"ipv6 option headers",			_4bytes,  _4bytes,  0 },

        { Vendor_Proprietary_65,  	 	 	(char*)"Vendor Proprietary 65",			_0byte,   _0byte,   0 },
        { Vendor_Proprietary_66,  	 	 	(char*)"Vendor Proprietary 66",			_0byte,   _0byte,   0 },
        { Vendor_Proprietary_67,  	 	 	(char*)"Vendor Proprietary 67",			_0byte,   _0byte,   0 },
        { Vendor_Proprietary_68,  	 	 	(char*)"Vendor Proprietary 68",			_0byte,   _0byte,   0 },
        { Vendor_Proprietary_69,  	 	 	(char*)"Vendor Proprietary 69",			_0byte,   _0byte,   0 },


        // mpls
        { NF9_MPLS_LABEL_1, 	 	        (char*)"mpls label 1",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_2, 	 	        (char*)"mpls label 2",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_3, 	 	        (char*)"mpls label 3",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_4, 	 	        (char*)"mpls label 4",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_5, 	 	        (char*)"mpls label 5",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_6, 	 	        (char*)"mpls label 6",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_7, 	 	        (char*)"mpls label 7",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_8, 	 	        (char*)"mpls label 8",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_9, 	 	        (char*)"mpls label 9",		_3bytes,  _4bytes,  0 },
        { NF9_MPLS_LABEL_10, 	 	        (char*)"mpls label 10",		_3bytes,  _4bytes,  0 },

        { NF9_IN_DST_MAC, 		 	(char*)"in dst mac",			_6bytes,  _8bytes,  0 },
        { NF9_OUT_SRC_MAC, 		 	(char*)"out src mac",			_6bytes,  _8bytes,  0 },

        { IF_NAME , 		 	    (char*)"if name",			_72bytes,  _72bytes,  0 },
        { IF_DESC, 		 	        (char*)"if desc ",			_72bytes,  _72bytes,  0 },
        { SAMPLER_NAME , 		 	(char*)"sampler name ",			_6bytes,  _8bytes,  0 },
        { IN_PERMANENT_BYTES, 		(char*)"in permanent byts ",			_4bytes,  _4bytes,  0 },
        { IN_PERMANENT_PKTS, 		(char*)" in permanent pkts ",			_4bytes,  _4bytes,  0 },
        { Vendor_Proprietary_87, 	(char*)" Vendor Proprietary",			_0byte,  _0byte,  0 },
        { FRAGMENT_OFFSET, 		 	(char*)"fragment offset ",			_2bytes,  _2bytes,  0 },

        { NF9_FORWARDING_STATUS, 	    (char*)"fwd status",			_1byte,   _1byte,   0 },

        { MPLS_PAL_RD, 	                (char*)"mpls pal rd",			_72bytes,   _72bytes,   0 },
        { MPLS_PREFIX_LEN, 	            (char*)"MPLS PREFIX LEN",			_1byte,   _1byte,   0 },
        { SRC_TRAFFIC_INDEX, 	        (char*)"SRC TRAFFIC INDEX",			_4bytes,   _4bytes,   0 },
        { DST_TRAFFIC_INDEX, 	        (char*)"DST TRAFFIC INDEX",			_4bytes,   _4bytes,   0 },
        { APPLICATION_DESCRIPTION, 	    (char*)"APPLICATION DESCRIPTION",			_72bytes,   _72bytes,   0 },
        { APPLICATION_TAG, 	            (char*)"APPLICATION TAG",			    _1byte,   _72bytes,   0 },

        { APPLICATION_NAME, 	        (char*)"APPLICATION NAME",			_1byte,   _72bytes,   0 },
        { postipDiffServCodePoint, 	    (char*)"APPLICATION TAG",	    _1byte,   _1byte,   0 },
        { replication_factor, 	        (char*)"replication factor",			_4bytes,   _4bytes,   0 },
        { DEPRECATED, 	                (char*)"DEPRECATED",			        _72bytes,   _72bytes,   0 },
        { layer2packetSectionOffset, 	    (char*)"layer2packetSectionOffset",			_0byte,   _0byte,   0 },
        { layer2packetSectionSize, 	        (char*)"layer2packetSectionSize ",			_0byte,   _0byte,   0 },
        { layer2packetSectionData, 	        (char*)"layer2packetSectionData ",			_0byte,   _0byte,   0 },


        { NF9_BGP_ADJ_NEXT_AS, 	 	        (char*)"BGP next AS",			_4bytes,  _4bytes,  0 },
        { NF9_BGP_ADJ_PREV_AS, 	 		    (char*)"BGP prev AS",			_4bytes,  _4bytes,  0 },
        // NSEL ASA extension
        // NSEL common
        { NF_F_EVENT_TIME_MSEC,	    (char*)"ASA event time",		_8bytes,  _8bytes,  0 },
        { NF_F_CONN_ID, 	 		(char*)"ASA conn ID",			_4bytes,  _4bytes,  0 },
        { NF_F_FW_EVENT84, 		 	(char*)"ASA event 84",			_1byte,   _1byte,   0 },
        { NF_F_FW_EVENT, 		 	(char*)"ASA event",			_1byte,   _1byte,   0 },
        { NF_F_FW_EXT_EVENT, 		(char*)"ASA ext event",		_2bytes,  _2bytes,  0 },
        { NF_F_ICMP_TYPE, 			(char*)"ASA ICMP type",		_1byte,   _1byte,   0 },
        { NF_F_ICMP_CODE, 			(char*)"ASA ICMP code",		_1byte,   _1byte,   0 },
        { NF_F_ICMP_TYPE_IPV6, 			(char*)"ASA ICMP type V6",		_1byte,   _1byte,   0 },
        { NF_F_ICMP_CODE_IPV6, 			(char*)"ASA ICMP code V6",		_1byte,   _1byte,   0 },
        { NF_F_FLOW_CREATE_TIME_MSEC,	(char*)"ASA flow create",		_8bytes,  _8bytes,  0 },
        // XlATE extensions
        { NF_F_XLATE_SRC_ADDR_IPV4, 	(char*)"ASA V4 xsrc addr",		_4bytes,  _4bytes,  0 },
        { NF_F_XLATE_DST_ADDR_IPV4,		(char*)"ASA V4 xdst addr",		_4bytes,  _4bytes,  0 },
//	{ NF_F_XLATE_SRC_ADDR_IPV6,(char*)"ASA V6 xsrc addr",		_16bytes, _16bytes, move128, zero128, 0 },
//	{ NF_F_XLATE_DST_ADDR_IPV6,(char*)"ASA V6 xdst addr",		_16bytes, _16bytes, move128, zero128, 0 },
        { NF_F_XLATE_SRC_PORT, 			(char*)"ASA xsrc port",		_2bytes,  _2bytes,  0 },
        { NF_F_XLATE_DST_PORT, 			(char*)"ASA xdst port",		_2bytes,  _2bytes,  0 },
        // ACL extension
        { NF_F_INGRESS_ACL_ID, 			(char*)"ASA ingress ACL",		_12bytes,  _12bytes, 0 },
        { NF_F_EGRESS_ACL_ID, 			(char*)"ASA egress ACL",		_12bytes,  _12bytes, 0 },
        // byte count
        { NF_F_FLOW_BYTES, 			(char*)"ASA bytes",			_4bytes,  _8bytes,  0 },
        { NF_F_FLOW_BYTES, 			(char*)"ASA bytes",			_8bytes,  _8bytes,  0 },
        { NF_F_FWD_FLOW_DELTA_BYTES, 		(char*)"ASA fwd bytes",		_4bytes,  _8bytes,  0 },
        { NF_F_FWD_FLOW_DELTA_BYTES, 		(char*)"ASA fwd bytes",		_8bytes,  _8bytes,  0 },
        { NF_F_REV_FLOW_DELTA_BYTES, 		(char*)"ASA rew bytes",		_4bytes,  _4bytes,  0 },
        { NF_F_REV_FLOW_DELTA_BYTES, 		(char*)"ASA rew bytes",		_8bytes,  _8bytes,  0 },
        // NSEL user names
        { NF_F_USERNAME, 			(char*)"ASA user name 20",		_20bytes, _24bytes, 0 },
        { NF_F_USERNAME, 			(char*)"ASA user name 65",		_65bytes, _72bytes, 0 },

        // NEL CISCO ASR 1000 series NAT logging
        // NEL COMMON extension
        { NF_F_EVENT_TIME_MSEC,			(char*)"NEL event time",		_8bytes,  _8bytes,  0 },
        { NF_N_NAT_EVENT, 		 		(char*)"NEL NAT event",	_1byte,   _1byte,   0 },
        { NF_N_POST_NAPT_SRC_PORT,		(char*)"NEL xsrc port",		_2bytes,  _2bytes,  0 },
        { NF_N_POST_NAPT_DST_PORT, 		(char*)"NEL xdst port",		_2bytes,  _2bytes,  0 },
        { NF_N_INGRESS_VRFID, 	 		(char*)"NEL ingress VRFID",	        _4bytes,  _4bytes,  0 },
        // NEL GLOBAL IP extensions
        { NF_N_NAT_INSIDE_GLOBAL_IPV4, 		(char*)"NEL V4 inside IP",		_4bytes,  _4bytes,  0 },
        { NF_N_NAT_OUTSIDE_GLOBAL_IPV4, 	(char*)"NEL V4 outside IP",		_4bytes,  _4bytes,  0 },
//	{ NF_N_NAT_INSIDE_GLOBAL_IPV6,	(char*)"NEL V6 inside IP",			_16bytes, _16bytes, 0 },
//	{ NF_N_NAT_OUTSIDE_GLOBAL_IPV6,(char*)"NEL V6 outside IP",	_16bytes, _16bytes, 0 },

        // nprobe latency extension
        { NF9_NPROBE_CLIENT_NW_DELAY_USEC, 	(char*)"NPROBE client lat usec",	_4bytes,  _8bytes,  0 },
        { NF9_NPROBE_SERVER_NW_DELAY_USEC, 	(char*)"NPROBE server lat usec",	_4bytes,  _8bytes,  0 },
        { NF9_NPROBE_APPL_LATENCY_USEC, 	(char*)"NPROBE appl lat usec",	_4bytes,  _8bytes,  0 },
        { NF9_NPROBE_CLIENT_NW_DELAY_SEC, 	(char*)"NPROBE client lat sec",	_4bytes,  _8bytes,  0 },
        { NF9_NPROBE_SERVER_NW_DELAY_SEC, 	(char*)"NPROBE server lat sec",	_4bytes,  _8bytes,  0 },
        { NF9_NPROBE_APPL_LATENCY_SEC, 	 	(char*)"NPROBE appl lat sec",		_4bytes,  _8bytes,  0 },

        {0,(char*)"NULL",	0, 0}
};

uint32_t temp_creator( char *data,uint32_t data_size, uint32_t feald);
void sendv9templat();
void *start_temp_thread(void *data);
//uint32_t template_form[]={	NF9_IN_PROTOCOL,
//							NF9_L4_DST_PORT,
//							NF9_L4_SRC_PORT,
//							NF9_IPV4_DST_ADDR,
//							NF9_IPV4_SRC_ADDR,
//							NF9_IN_SRC_MAC,
//							NF9_OUT_DST_MAC,
//							NF9_TCP_FLAGS,
//							NF9_IN_BYTES,
//							NF9_IN_PACKETS,
//							NF9_IPV6_SRC_ADDR,
//							NF9_IPV6_DST_ADDR,
//						};


#endif /* SRC_V9NETFLOWTEMP_H_ */
