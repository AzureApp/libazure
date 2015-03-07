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
{
    serverReady = false;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        AZLog("Could not create socket\n"); //TODO: change to AZLog
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1248);
}

void Daemon::Start()
{
    bind(socket_desc, (struct sockaddr *)&server , sizeof(server));
    listen(socket_desc , 5);
    c = sizeof(struct sockaddr_in);
    accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
}

void Daemon::OnLostConnection()
{
    serverReady = false;
}

kern_return_t Daemon::ReceivedMessage(Message& message)
{
    long chunk_size = 64;
    if (serverReady)
    {
        msg_header header = header_default;
        long bytes = recv(client_sock, &header, sizeof(msg_header), 0);
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
                    if (bytes <= 0)
                    {
                        OnLostConnection();
                        return KERN_FAILURE;
                    }
                    read_size += bytes;
                }
            }
            message.header = header;
            message.message = data;
            return KERN_SUCCESS;
        }
    }
    return KERN_FAILURE;
}


kern_return_t Daemon::SendMessage(Message& message)
{
    long chunk_size = 64;
    if (serverReady)
    {
        char *data = (char*)message.message;
        send(client_sock, &message.header, sizeof(msg_header), 0);
        
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
                if (writeval <= 0)
                {
                    OnLostConnection();
                    return KERN_FAILURE;
                }
                write_size += writeval;
            }
        }
        return KERN_SUCCESS;
    }
    return KERN_FAILURE;
}

void Daemon::SendMessageReceiveSuccess()
{
    Message msg;
    msg.header = header_default;
    msg.header.type = StatusOK;
    
    this->SendMessage(msg);
}

