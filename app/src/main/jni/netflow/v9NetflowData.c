#include <stdio.h>
#include <stdint.h>


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "v9NetflowData.h"
#include "config.h"
#include "common/utils.h"


uint32_t data_location = -1;

unsigned int a = 15, b = 10;
uint32_t data_counder=0;
uint8_t  converted_data[150] = "";
uint8_t *data = NULL;

uint16_t number_of_flow_in = 1;
uint32_t starting_point_of_data_location = 0;


uint16_t for_temp =0;
uint16_t one_flow_size =0;
uint16_t one_flowset_size =0;
uint16_t array_size_out=0;
uint16_t udp_packet_data_size = sizeof(struct iphdr) + sizeof(struct udphdr);

//Datagram to represent the packet
uint8_t datagram[4096];

uint32_t template_form[]= {	  NF9_IN_PROTOCOL,
                              NF9_L4_DST_PORT,
                              NF9_L4_SRC_PORT,
                              NF9_IPV4_DST_ADDR,
                              NF9_IPV4_SRC_ADDR,
                              NF9_IN_SRC_MAC,
                              NF9_OUT_DST_MAC,
                              NF9_TCP_FLAGS,
                              NF9_IN_BYTES,
                              NF9_IN_PACKETS,
                              NF9_IPV6_SRC_ADDR,
                              NF9_IPV6_DST_ADDR,
                              NF9_FLOW_ACTIVE_TIMEOUT,
                              NF9_FIRST_SWITCHED,
                              NF9_LAST_SWITCHED
                          };


void V9Datahedder(){
    //	uint32_t template_form[]={11,7,12,8,56,57,6,10,14,2,1};
    //	uint32_t template_form[]={4,11,7,12,8,56,57,6,1,2,27,28};


    uint32_t sizeof_temp  = sizeof(template_form)/sizeof(template_form[0]);

    //zero out the packet buffer
    memset (datagram, 0, 4096);

    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);

    for(for_temp =0; for_temp < sizeof_temp;for_temp++)  one_flow_size = one_flow_size + v9_element_map[template_form[for_temp]].length;

    one_flowset_size = htons((one_flow_size*number_of_flow_in) +  NF9_DATA_FLOWSET_ID_SIZE + NF9_DATA_FLOWSET_LENTH_SIZE); //*4 the num of flow// 4 is the flow set id and flow set length
    udp_packet_data_size =  htons(one_flowset_size)+sizeof(struct iphdr) + sizeof(struct udphdr); //udp_packet_data_size+
    netflow_header(converted_data,htons(9),htons(5),htonl(2566565),htonl(12334),htonl(234234),htonl(0), &array_size_out); //version,count,sysUpTime,TimeStamp,flowsequence,sorceid

    uint16_t f= 0;
    for(f=0;f<array_size_out;f++) data[++data_location] = converted_data[f];

    uint16_t temp_id = htons(Temp_264);
    data[++data_location] = temp_id;
    data[++data_location] = temp_id >> 8;
    data[++data_location] = one_flowset_size;
    data[++data_location] = one_flowset_size >>8;
    starting_point_of_data_location = data_location;

}

void V9DataGen(flowstructur_s *pack,uint8_t len){

    log_d("netflow pack->in_pkts %d",pack->in_pkts);
//    if (!pack->in_pkts)
//        return;



//	uint32_t template_form[]={4,11,7,12,21,22,8,56,57,6,1,2,27,28};
    uint32_t sizeof_temp  = sizeof(template_form)/sizeof(template_form[0]);
//    log_d("netflow gen %d",pack->in_pkts);

    int flow = 0;
    for(flow = 0;flow < number_of_flow_in;flow++)

    {
        uint32_t for_data_ = 0;
        for(for_data_ =0;for_data_ < sizeof_temp;for_data_++)
        {

            uint32_t template_elament = template_form[for_data_];
            uint16_t feeld_lenth = v9_element_map[template_elament].length;
            netflow_temp_function_serch(template_elament,converted_data,pack, len);
            //	const char *functionname = (*fun_ptr_arr[template_elament])(converted_data,a, b);
//            log_d("netflow gen template_elament %d %d %s",template_elament,feeld_lenth,v9_element_map[template_elament].name);
            for(data_counder=0;data_counder<feeld_lenth;data_counder++)
                data[++data_location] = converted_data[data_counder];
        }

    }


    sendData((char *)data,udp_packet_data_size,NETFLOWCLIENTIP,DSTPORT);

    data_location = starting_point_of_data_location;

    //	exit(1);


}
