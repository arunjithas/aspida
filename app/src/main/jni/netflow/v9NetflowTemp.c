
//#define _BSD_SOURCE

#include<stdio.h>
#include<stdlib.h>

#include<sys/time.h>
#include<arpa/inet.h> // For htons()
#include<string.h>
#include<stdint.h> // For uint32_t

#include<sys/socket.h>
#include<errno.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include<unistd.h>


#include "transmitter.h"
#include "v9NetflowTemp.h"
#include "config.h"


uint32_t temp_creator( char *data,uint32_t data_size, uint32_t feald);
uint32_t msTimeDiff(struct timeval end, struct timeval begin);


uint32_t timeval_sub_ms(const struct timeval *t1, const struct timeval *t2);

static struct timeval initialSniffTime;
static struct timeval actTime;




void v9NetflowTemp() {

    // Start a thread to execute sendv9templat() member function

//    std::cout<<"this is the v9NetflowTemp\n";
//    std::thread t([this]() { start_temp_thread(); }); // Lambda function capturing 'this'
//    t.detach(); // Detach the thread (or join it depending on your requirements)

}

void *start_temp_thread(void *data){

    for(;;){
        sendv9templat();
        sleep(TEMPLATESENDDELAY);

    }
}

uint32_t temp_creator( char *data,uint32_t data_size, uint32_t feald){


    data[++data_size] = v9_element_map[feald].id >> _8bytes;
    data[++data_size] = v9_element_map[feald].id;
    data[++data_size] = v9_element_map[feald].length >> _8bytes;
    data[++data_size] = v9_element_map[feald].length	;

    // printf("this ---------%d ---- %d",field_type,field_lenth);

    return data_size;

}


uint32_t msTimeDiff(struct timeval end, struct timeval begin) {
    if((end.tv_sec == 0) && (end.tv_usec == 0))
        return(0);
    else
        return((end.tv_sec-begin.tv_sec)*1000+(end.tv_usec-begin.tv_usec)/1000);
}

uint32_t timeval_sub_ms(const struct timeval *t1, const struct timeval *t2)
{
    struct timeval res;

    res.tv_sec = t1->tv_sec - t2->tv_sec;
    res.tv_usec = t1->tv_usec - t2->tv_usec;
    if (res.tv_usec < 0) {
        res.tv_usec += 1000000L;
        res.tv_sec--;
    }
    return ((uint32_t)res.tv_sec * 1000 + (uint32_t)res.tv_usec / 1000);
}

void sendv9templat(){
    //Datagram to represent the packet
    uint8_t datagram[4096]  , *data ;
    uint32_t data_location = 0;
//	uint32_t template_form[]={11,7,12,8,56,57,6,10,14,2,1};
//	uint32_t template_form[]={4,11,7,12,8,56,57,6,1,2,27,28};
//	uint32_t template_form[]={4,11,7,12,8,56,57,6,1,2,27,28,56,57};
    uint32_t template_form[]={	NF9_IN_PROTOCOL,
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

//	uint32_t template_form[]={4,11,7,12,21,22,8,56,57,6,1,2,27,28};


    uint16_t sizeof_temp = htons(sizeof(template_form)/sizeof(template_form[0]));

//	std::cout<<"sizeof_temp "<<sizeof_temp<<std::endl;

    //zero out the packet buffer
    memset (datagram, 0, 4096);
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
//	printf("---===->%s\n",data);





    gettimeofday(&initialSniffTime, NULL);

    gettimeofday(&actTime, NULL);


    /****** net flow version*****/
    data[data_location]   = NETFLOW_VERTION >>8;
    data[++data_location] = NETFLOW_VERTION;
    /****************************/


    /*********coubt of flow sets******/
    data[++data_location] = 0X00;
    data[++data_location] = COUNT_OF_FLOWS;
    /****************************/



    /***** system uptime ******/
    uint32_t system_uptime = htonl(msTimeDiff(actTime,initialSniffTime));

    data[++data_location] = system_uptime;
    data[++data_location] = system_uptime >> 8;
    data[++data_location] = system_uptime >> 16;
    data[++data_location] = system_uptime >> 24;

    /****************************/



    /***** Time Stamp ***********/

    uint32_t time_stamp = 0;//htonl(actTime.tv_sec);

    data[++data_location] = time_stamp;
    data[++data_location] = time_stamp >> 8;
    data[++data_location] = time_stamp >> 16;
    data[++data_location] = time_stamp >> 24;

    /***************************/



    /*********** sequence number *****/
    uint32_t sequence_number = htonl(27372);
    data[++data_location] 	 = sequence_number;
    data[++data_location]    = sequence_number >> 8;
    data[++data_location]    = sequence_number >> 16;
    data[++data_location]    = sequence_number >> 24;


    /*********************************/


    /************* sorce id *********/

    uint32_t sorce_id = htonl(0);
    data[++data_location] = sorce_id;
    data[++data_location] = sorce_id >> 8;
    data[++data_location] = sorce_id >> 16;
    data[++data_location] = sorce_id >> 24;

    uint16_t flowset_id = htons(0);

    data[++data_location] = flowset_id ;
    data[++data_location] = flowset_id >>8 ;
    /************************************/

    data[++data_location] = sizeof_temp;
    data[++data_location] = sizeof_temp >>8;



    uint16_t field_count =0;
    field_count = sizeof(template_form) ;
    field_count = (field_count/sizeof(uint32_t));
//	std::cout<<"field_count - " <<field_count<<std::endl;

//	uint16_t udp_packet_data_size = (field_count * _4bytes)+_4bytes+_4bytes+sizeof(struct iphdr) + sizeof(struct udphdr); //udp_packet_data_size+
    uint16_t udp_packet_data_size = (field_count * _4bytes)+sizeof(struct iphdr) + sizeof(struct udphdr); //udp_packet_data_size+

//	printf("---udp_packet_data_size->%d\n", udp_packet_data_size);
    data[++data_location] = Temp_264 >>_8bytes;
    data[++data_location] = (uint8_t)Temp_264;
    data[++data_location] = field_count >>_8bytes;
    data[++data_location] = field_count;




//	unsigned int ch;
//	printf("enter a number for starting for template sending : ");
//	int scan_size = scanf("%d", &ch);
//	printf("scan_size %d\n",scan_size);

    int i =0;
    for(i=0;i<field_count;i++){

        data_location = temp_creator((char *)data,data_location,template_form[i]);


    }


//    sendData((char *)data,udp_packet_data_size,NETFLOWGENSERVERSRCIP,NETFLOWCLIENTIP,NETFLOWGENSERVERSRCSRCPORT,DSTPORT);
//	sendData((char *)data,udp_packet_data_size,"10.10.10.10","10.10.3.9",100,2055);
    sendData((char *)data,udp_packet_data_size,NETFLOWCLIENTIP,DSTPORT);


//	return 0;

}

//Complete


