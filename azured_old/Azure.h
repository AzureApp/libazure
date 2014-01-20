//
//  Azure.h
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#ifndef __azured__Azure__ 
#define __azured__Azure__

#include <iostream>
#include <vector>
class CommsEngine;
using namespace std;
class Azure
{
public:
    struct AzureGlobalSettings
    {
        bool debug;
        int startaddr;
        int endaddr;
        int chunksize;
        
    };
    CommsEngine *m_comm;
    
    Azure();
    ~Azure();
    void AzureInit();
    void WriteToLog(const char * message);
    int AzureTick();
};
extern struct Azure::AzureGlobalSettings *settings;
extern Azure *g_azure;

#endif /* defined(__azured__Azure__) */
