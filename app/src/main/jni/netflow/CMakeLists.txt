project(netflow C)

ADD_LIBRARY(netflow STATIC transmitter.c dataExtractionfunctions.c
        v9NetflowTemp.c v9NetflowData.c blackListIps.c
        dataParser.c snifferentrypoint.c)
