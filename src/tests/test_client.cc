#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "shared.h"

int main() {
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(1248);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    while (true) {
//        /*---- Read the message from the server into the buffer ----*/
//        recv(clientSocket, buffer, 1024, 0);
//
//        /*---- Print the received message ----*/
//        printf("Data received: %s", buffer);
//
//        send(clientSocket, "pong\n", 6, 0);

        std::vector<char> bytes;
        bytes.reserve(sizeof(azure::MetaObject));

        recv(clientSocket, &bytes[0], sizeof(azure::MetaObject), MSG_PEEK);

        msgpack::object_handle handle = msgpack::unpack(bytes.data(), bytes.size());
        msgpack::object msgObj = handle.get();

        azure::MetaObject meta = msgObj.convert();

        if (meta.type == azure::MetaObject::Type::Data) {
            // should never be reached in production
            recv(clientSocket, &bytes[0], sizeof(azure::MetaObject), 0);

            handle = msgpack::unpack(bytes.data(), bytes.size());
            msgObj = handle.get();

            azure::MetaObject dataObj = msgObj.convert();

            PrintDataObject(dataObj);
        } else if (meta.type == azure::MetaObject::Type::Search) {
            bytes.resize(sizeof(azure::SearchObject));

            recv(clientSocket, &bytes[0], sizeof(azure::MetaObject), 0);

            handle = msgpack::unpack(bytes.data(), bytes.size());
            msgObj = handle.get();

            azure::SearchObject searchObj = msgObj.convert();

            PrintDataObject(searchObj);
        }

        azure::MetaObject dataObj2 = azure::MetaObject(azure::MetaObject::Type::Data);

        msgpack::sbuffer buffer;
        msgpack::pack(buffer, dataObj2);

        send(clientSocket, buffer.data(), buffer.size(), 0);
    }
}
