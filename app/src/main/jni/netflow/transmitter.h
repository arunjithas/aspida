

#ifndef SRC_TRANSMITTER_H_
#define SRC_TRANSMITTER_H_

int send_data_to_server();
int sendData(char *pydata, int pydatalen,const char *dstIP,int dstport);
#endif /* SRC_TRANSMITTER_H_ */
