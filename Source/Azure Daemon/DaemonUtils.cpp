//
//  DaemonUtils.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 14/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "DaemonUtils.h"

using namespace DaemonUtils;

static void connect_helper(Daemon*, int);

Daemon::Daemon()
{
    serverReady = false;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket"); //TODO: change to AZLog
        exit(1);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1248);
    
    bind(socket_desc, (struct sockaddr *)&server , sizeof(server));
//    client_sock = Connect();
//    serverReady = true;
//    std::thread connection(connect_helper, this, client_sock);
//    connection.detach();
}

void Daemon::Start()
{
    if (serverReady)
    {
        Tick();
    }
    else
    {
        client_sock = Connect();
        serverReady = true;
        Tick();
    }
}

int Daemon::Connect()
{
    listen(socket_desc , 5);
    c = sizeof(struct sockaddr_in);
    return accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
}

int Daemon::Tick()
{
    if (!serverReady)
    {
        client_sock = Connect();
        if(client_sock != -1)
        {
            serverReady = true;
            std::thread connection(connect_helper, this, client_sock);
            connection.detach();
        }
    }
    return 0;
}

static inline void connect_helper(Daemon *passthrough, int sock)
{
    return passthrough->OnNewConnection(sock);
}

void Daemon::OnNewConnection(int sock)
{
    printf("new connection\n");
    while (true)
    {
        usleep(100);
        if (IsConnected())
        {
            ReceiveMessage();
        }
        else
        {
            return OnLostConnection();
        }
    }
}

bool Daemon::IsConnected()
{
    char c;
    long status = recv(client_sock, &c, 1, MSG_PEEK);
    return (status > 0);
}

void Daemon::OnLostConnection()
{
    serverReady = false;
    // additional processes?
}

void Daemon::ReceiveMessage()
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
                    if (bytes == -1)
                    {
                        OnLostConnection();
                    }
                    read_size += bytes;
                }
            }
            
            Message message;
            message.header = header;
            message.message = data;
            Messaging::GetInstance()->PushMessage(message);
        }
    }
}


void Daemon::SendMessage(Message& message)
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
                    return OnLostConnection();
                }
                write_size += writeval;
            }
        }
    }
}

