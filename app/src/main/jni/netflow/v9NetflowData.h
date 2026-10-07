

#ifndef SRC_V9NETFLOWDATA_H_
#define SRC_V9NETFLOWDATA_H_


#include<netinet/udp.h>
#include<netinet/ip.h>

#include "datastructur.h"
#include "transmitter.h"
#include "dataExtractionfunctions.h"
#include "v9NetflowTemp.h"

void V9Datahedder();
void V9DataGen(flowstructur_s *pack,uint8_t len);



#endif /* SRC_V9NETFLOWDATA_H_ */
