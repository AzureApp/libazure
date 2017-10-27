#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <msgpack.hpp>

#include "../libazure/data_objects/search_object.h"
#include "shared.h"

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1248);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    while(1) {
      ResultObject obj({
        {0x10000, {0xC0, 0x46}},
        {0x3FE800, {0x1E, 0xFF, 0x2F, 0xE2}}
      });

        SendObject(connfd, obj);
        sleep(1);

        ResultObject meta = RecvObject(connfd);
        PrintDataObject(meta);
    }
}
