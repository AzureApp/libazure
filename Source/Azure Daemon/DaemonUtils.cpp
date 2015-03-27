//
//  DaemonUtils.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 14/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "DaemonUtils.h"
#include "Azure.h"

using namespace DaemonUtils;

Daemon::Daemon()
: serverReady(false), port(DAEMON_PORT)
{
    std::signal(SIGPIPE, SIG_IGN);
}

Daemon::~Daemon()
{
    if (serverReady)
    {
        this->Close();
    }
}

AZ_STATUS Daemon::Start()
{
    AZLog("starting daemon");
    
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        AZLog("Could not create socket");
        return AZ_FAILURE;
    }
    int set = 1;
    setsockopt(socket_desc, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    bind(socket_desc, (struct sockaddr *)&server , sizeof(server));
    listen(socket_desc , 5);
    c = sizeof(struct sockaddr_in);
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    
    serverReady = true;
    return AZ_SUCCESS;
}

void Daemon::Close()
{
    AZLog("daemon shutting down");
    close(socket_desc);
    client_sock = -1;
    serverReady = false;
}

void Daemon::OnLostConnection()
{
    AZLog("daemon lost connection");
    
    this->serverReady = false;
    this->Close();
}

AZ_STATUS Daemon::ReceivedMessage(Message& message)
{
    long chunk_size = 64;
    if (serverReady)
    {
        msg_header header = header_default;
        long bytes = recv(client_sock, &header, sizeof(msg_header), 0);
        if (bytes < 0)
        {
            this->OnLostConnection();
            return AZ_FAILURE;
        }
        
        char *data = NULL;
        if (bytes > 0)
        {
            long msg_size = header.messageSize;
            if (msg_size > 0)
            {
                long read_size = 0;
                data = (char*)malloc(msg_size);
                while (read_size <= msg_size)
                {
                    if ((read_size + chunk_size) > msg_size)
                    {
                        chunk_size = msg_size - read_size;
                        if (chunk_size == 0) break;
                    }
                    long bytes = recv(client_sock, data+read_size, chunk_size, 0);
                    AZLog("%d", bytes);
                    if (bytes < 0)
                    {
                        AZLog("testy mctest");
                        this->OnLostConnection();
                        return AZ_FAILURE;
                    }
                    read_size += bytes;
                }
            }
            message.message = data;
        }
        message.header = header;
        AZLog("received message of type %s", enumToName(message.header.type));
        return AZ_SUCCESS;
    }
    return AZ_FAILURE;
}


AZ_STATUS Daemon::SendMessage(Message& message)
{
    AZLog("sending message of type %s", enumToName(message.header.type));
    long chunk_size = 64;
    if (serverReady)
    {
        char *data = (char*)message.message;
        long sent = send(client_sock, &message.header, sizeof(msg_header), 0);
        if (sent < 0)
        {
            AZLog("testy mctest 2");
            this->OnLostConnection();
            return AZ_FAILURE;
        }
        
        long msg_size = message.header.messageSize;
        if (msg_size > 0)
        {
            long write_size = 0;
            
            while (write_size <= msg_size)
            {
                if ((write_size + chunk_size) > msg_size)
                {
                    chunk_size = msg_size - write_size;
                    if (chunk_size == 0) break;
                }
                long writeval = send(client_sock, data+write_size, chunk_size, 0);
                if (writeval < 0)
                {
                    AZLog("testy mctest 2");
                    this->OnLostConnection();
                    return AZ_FAILURE;
                }
                write_size += writeval;
            }
        }
        return AZ_SUCCESS;
    }
    return AZ_FAILURE;
}

void Daemon::SendMessageReceiveSuccess()
{
    Message msg;
    msg.header = header_default;
    msg.header.type = StatusOK;
    
    this->SendMessage(msg);
}

