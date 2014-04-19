//
//  Messaging.h
//  Azure
//
//  Created by callum taylor on 08/02/2014.
//
//

#ifndef __Azure__Messaging__
#define __Azure__Messaging__

#include <iostream>
#include <unistd.h>
#include "Azure.h"

using namespace std;
enum MessageType
{
    m_Attach,
    m_NewSearch,
    m_IterateSearch,
    m_WriteValue,
    m_LockValue,
    m_UnlockValue,
    m_Null
};



struct Message 
{
    MessageType type;
    DataObject *dataPtr;
    bool shouldPop;
};

class ExternalMessaging 
{
   //only used in daemon, not command line
};

class InternalMessaging 
{
public:
    static InternalMessaging *az_msg;
    InternalMessaging();
    static vector<struct Message> *messageStack;
    static InternalMessaging* instance();
    
    void PushMessage(MessageType type, DataObject *obj);
    static void* BeginMessagingSystem(void*);
    int ProcessMessage(Message message);
    void PopMessage(int);
};

#endif /* defined(__Azure__Messaging__) */