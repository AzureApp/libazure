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
    bool Debug;
    CommsEngine *m_comm;
    
    Azure();
    ~Azure();
    void WriteToLog(const char * message);
    int AzureTick();
};
extern Azure *g_azure;
#endif /* defined(__azured__Azure__) */
