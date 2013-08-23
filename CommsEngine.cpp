//
//  CommsEngine.cpp
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#include "Combined.h"

int CommsEngine::Init()
{
    portno = 54982;//Random Constant Port
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        g_azure->WriteToLog("Azure error: ERROR opening socket\n");
        return SocketFailed;
    }
    server = gethostbyname("192.175.5.248");//192.175.5.248 = random private ipaddress CONSTANTa
    if (server == NULL) {
        g_azure->WriteToLog("Azure error: ERROR, no such host\n");
        return HostFailed;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        g_azure->WriteToLog("Azure error: ERROR connecting\n");
    
    return 0;
}

void CommsEngine::SendMessage(const char *message)
{
    int n;
    bzero(writebuffer,1024);
    printf(writebuffer, message);
    n = write(sockfd,writebuffer,strlen(writebuffer));
    if (n < 0)
        g_azure->WriteToLog("Azure error: ERROR writing to socket\n");
}
const char* CommsEngine::ReadMessage()
{
    int n;
    bzero(readbuffer,1024);
    n = read(sockfd,readbuffer,1023);
    if (n < 0)
        g_azure->WriteToLog("Azure error: ERROR reading from socket\n");
    return readbuffer;
}

void CommsEngine::ConnectionKeepAlive(/*args?*/)
{
    int n;
    n =  write(sockfd,"_",1);
    if(n<0)
        g_azure->WriteToLog("Azure error: Failed To Keep Connection Alive.\n");
}

void CommsEngine::ProcessMessage(const char *message)
{
    char *message1 = (char*)message;
    char *tempmessage;
    tempmessage = strtok(message1,"&");
    
    char *messages[10]; //Max 10 messages at a time
    
    for(int x;x<10;x++)
        messages[x] = (char*)""; //To Not Get Null Error
    
    int i = 0;
    while(tempmessage != NULL)
    {
        messages[i] = tempmessage;
        tempmessage = strtok(NULL, "&");
        i++;
    }
    
    for(int j = 0; j<10;j++)
    {
        if(strcmp(messages[j],"") != 0)
        {
            //Process Messages Here
            
            /*
             search(number)
             edit(address, value)
             lock(address, value)
             unlock(address)
             search(value)
             kill(process)
             
             */
            char *args[4];//Max 4 args in a message
            char *tempargs;
            
            for(int z = 0;z<4;z++)
                args[z] = 0;
            
            tempargs = strtok(messages[j], "/");
            int y = 0;
            while(tempargs != NULL)
            {
                args[y] = tempargs;
                tempargs = strtok(NULL, "/");
                y++;
            }
            if(strcmp(args[0],"search") == 0)
            {
                g_number->SearchNumber((int)args[1]);
            }
            else if(strcmp(args[0],"lock") == 0)
            {
                g_memengine->Lock((uint)args[1],(int)args[2]);
            }
            else if(strcmp(args[0],"edit") == 0)
            {
                g_memengine->Edit((uint)args[1],(int)args[2]);
            }
            else if(strcmp(args[0],"unlock") == 0)
            {
                g_memengine->Unlock((uint)args[1]);
            }
            else if(strcmp(args[0],"kill") == 0)
            {
                g_memengine->KillProcess(args[1]);
            }
            
            /*
             lock(0x12420) as an example message, would tell the app to add 0x12420 to the lock vector
             read(0x12542) will read messages
             More than 1 action = lock(0x12420)&read(0x12542)
             Messages will be split using '&'
             */
        }
    }
}

CommsEngine::~CommsEngine()
{
    close(sockfd);
}