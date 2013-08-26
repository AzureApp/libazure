//
//  Azure.cpp
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#include "Combined.h" 
Azure *g_azure = NULL;

Azure::Azure()
{
    g_azure = this;
    Debug = 0;
    m_comm = new CommsEngine();
}

Azure::~Azure()
{
    
}

int Azure::AzureTick()
{
    const char *buffer;
    buffer = m_comm->ReadMessage();
    m_comm->ProcessMessage(buffer);
    
    /*
     check incoming messages
     process the message
     write to locked values
     Send message to  app as response to requests
     begin again
     */
}


void Azure::WriteToLog(const char * message)
{
    if (!Debug) {
        return;
    }
    FILE *outfile = fopen("/var/mobile/Azure/log.txt", "w");//Place + mode w = write
    fwrite(message, sizeof(char), sizeof(message), outfile); //args: 1=data, 2=size of 1 (byte*type) of data, 3=size of data, file
    fclose(outfile);
}
