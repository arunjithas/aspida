#define N_tap_VERSION_MAJOR 0
#define N_tap_VERSION_MINOR 1


#define NETWORKPACKETREVICEINTERFACE "ntap1"  // "wlp0s20f3" // "enp4s0f1" //


// SELD PACKET GERNARATOR DETAILS
#define NETFLOWGENSERVERSRCSRCPORT 100
#define NETFLOWGENSERVERSRCIP "10.10.10.10"



#define DSTPORT 		  2055
//#define NETFLOWCLIENTIP   "127.0.0.1"

//#define NETFLOWCLIENTIP "192.168.1.8"
#define NETFLOWCLIENTIP "10.10.3.82"




#define MAXPACKETINANETLFOW 100
#define MAXCASHINGTIME 		10



#define TEMPLATESENDDELAY 15


#define PRINT_LOCATION() \
    std::cout << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Function: " << __func__ << std::endl;

//#define PRINT_LOCATION() \
//    return 0;



