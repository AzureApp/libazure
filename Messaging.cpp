//
//  Messaging.cpp
//  Azure
//
//  Created by callum taylor on 08/02/2014.
//
//

#include "Messaging.h"

InternalMessaging* InternalMessaging::az_msg = NULL;
std::vector<struct Message> *InternalMessaging::messageStack = NULL;

InternalMessaging::InternalMessaging()
{
    messageStack = new vector<Message>;
    Message first = {m_Null, NULL, false};
    messageStack->push_back(first);
}

InternalMessaging* InternalMessaging::instance()
{
    if(!az_msg)
    {
        az_msg = new InternalMessaging();
    }
    
    return az_msg;
}

void InternalMessaging::PushMessage(MessageType type, DataObject *dataPtr)
{
    switch(type)
    {
        case m_Attach:
        {
            Message tmpMsg = {type, dataPtr, true};
            InternalMessaging::messageStack->push_back(tmpMsg);
            break;
        }
        case m_NewSearch:
        {
            Message tmpMsg = {type, dataPtr, true};
            InternalMessaging::messageStack->push_back(tmpMsg);
            break;
        }
        case m_IterateSearch:
        {
            Message tmpMsg = {type, dataPtr, true};
            InternalMessaging::messageStack->push_back(tmpMsg);
            break;
        }
        case m_WriteValue:
        {
            Message tmpMsg = {type, dataPtr, true};
            InternalMessaging::messageStack->push_back(tmpMsg);
            break;
        }
        case m_LockValue:
        {
            Message tmpMsg = {type, dataPtr, false};
            InternalMessaging::messageStack->push_back(tmpMsg);
            break;
        }
        case m_UnlockValue:
        {
            Message tmpMsg = {type, dataPtr, true};
            InternalMessaging::messageStack->push_back(tmpMsg);
            break;
        }
        default:
            AZLog("Messaging: error could not push message\n");
            break;
    }
    
}

void InternalMessaging::PopMessage(int pos)
{
    Message msg = InternalMessaging::messageStack->at(pos);
    delete msg.dataPtr;
    messageStack->erase(messageStack->begin()+pos);
}

void* InternalMessaging::BeginMessagingSystem(void*)
{
    InternalMessaging *im = InternalMessaging::instance();
    int i = 0;
    while (InternalMessaging::messageStack->size() > 0)
    {
        Message local = InternalMessaging::messageStack->at(i);
        int ret = im->ProcessMessage(local);
        if(ret != 0)
        {
            return NULL; //error
        }
        if (local.shouldPop)
        {
            im->PopMessage(i);
        }
        if(i+1 >= InternalMessaging::messageStack->size())
        {
            i=0;
        }
        else
        {
            i++;
        }
    }
    return NULL;
}

int InternalMessaging::ProcessMessage(Message message)
{
    //XXX: Make this much cleaner
    Azure *az_main = Azure::instance();
    MemoryManager *az_mem = MemoryManager::instance();
    ProcessInfo *az_proc = ProcessInfo::instance();
    switch (message.type)
    {
        case m_Attach:
        {
            Process temp;
            strcpy(temp.processName, (char*)message.dataPtr->data());//change this
            az_proc->AttachToProcess(temp);
            break;
        }
            
        case m_NewSearch:
        case m_IterateSearch:
        {
            SearchObject *srch = (SearchObject*)message.dataPtr->data();
            az_mem->Search(srch);
            break;
        }
        
        case m_WriteValue:
        {
            WriteObject *wobj = (WriteObject*)message.dataPtr->data();
            az_mem->WriteData(wobj);
            break;
        }
        case m_LockValue:
        {
            //add a value to lock array. see m_Null for iteration over locked data
            break;
        }
            
        case m_UnlockValue:
        {
            break;
        }
        case m_Null:
        {
            //iterate all locked values
            //pause for 0.1s or less
            for(int i = 0; i < az_mem->lockData->size(); i++)
            {
                LockData local = az_mem->lockData->at(i);
                WriteObject *wobj = new WriteObject(local.address, local.data, local.dataCnt);

                az_mem->WriteData(wobj);
                delete wobj;
            }
            usleep(100000); //right?
            break;
        }
            
        default:
            AZLog("Invalid message received\n");
            break;
    }
    return 0;
}

