//
//  Messaging.cpp
//  Azure
//
//  Created by callum taylor on 25/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "Messaging.h"
#include "Azure.h"

Messaging::Messaging()
{
    
}

Messaging::~Messaging()
{
    
}

Messaging* Messaging::GetInstance()
{
    static Messaging *instance = NULL;
    if (!instance)
    {
        instance = new Messaging();
    }
    return instance;
}

kern_return_t Messaging::Tick()
{
    kern_return_t status = KERN_SUCCESS;
    while (messageStack.size() > 0)
    {
        Message msg = messageStack.front();
        status = ProcessMessage(msg);
        if (msg.header.shouldPop)
        {
            PopMessage(0);
        }
        
        if (status != KERN_SUCCESS) break;
    }
    return status;
}

kern_return_t Messaging::ProcessMessage(Message& message)
{
    Azure *azure = Azure::GetInstance();
    MemoryManager *manager = MemoryManager::GetInstance();
    
    switch (message.header.type) {
            
        case StatusOK:
        case StatusErr:
            return KERN_SUCCESS; // not really useful
            
        case Attach:
        {
            msg_process *procData = (msg_process*)message.message;
            Process *proc = new Process(procData);
            kern_return_t status = ProcessUtils::TryAttach(proc);
            if (status == KERN_SUCCESS)
            {
                azure->AttachToProcess(proc);
                Message success = SuccessMessage();
                azure->CurrentDaemon()->SendMessage(success);
            }
            else
            {
                Message fail = FailMessage(NULL);
                azure->CurrentDaemon()->SendMessage(fail);
            }
            return status;
        }
        case Detach:
            // TODO
            break;
            
        case NewSearch:
        {
            void *pattern = message.message;
            size_t size = message.header.messageSize;
            std::vector<vm_address_t> addresses = manager->Find(pattern, size);
            vm_address_t *addressPtr = &addresses[0];
            
            Message msg = MessageFromResults(addressPtr, addresses.size()*sizeof(vm_address_t));
            azure->CurrentDaemon()->SendMessage(msg);
            
            return KERN_SUCCESS;
        }
            
        case IterateSearch:
        {
            void *pattern = message.message;
            size_t size = message.header.messageSize;
            std::vector<vm_address_t> addresses = manager->Iterate(pattern, size, manager->Results());
            
            vm_address_t *addressPtr = &addresses[0];
            Message msg = MessageFromResults(addressPtr, addresses.size()*sizeof(vm_address_t));
            azure->CurrentDaemon()->SendMessage(msg);
            
            return KERN_SUCCESS;
        }
//
//        case IterateSearch:
//            return "IterateSearch";
//            break;
//        case Edit:
//            return "Edit";
//            break;
//        case Lock:
//            return "Lock";
//            break;

    }
    return KERN_FAILURE;
}


void Messaging::PushMessage(Message& message)
{
    messageStack.push_back(message);
}

void Messaging::PopMessage(int pos)
{
    messageStack.erase(messageStack.begin()+pos);
}

Message Messaging::SuccessMessage()
{
    Message msg;
    msg.header = header_default;
    msg.header.messageSize = 0;
    msg.header.type = StatusOK;
    msg.message = NULL;
    
    return msg;
}

Message Messaging::FailMessage(const char *err)
{
    Message msg;
    msg.header = header_default;
    msg.header.messageSize = 0;
    msg.header.type = StatusErr;
    msg.message = NULL;
    if (err != NULL)
    {
        msg.header.messageSize = strlen(err);
        msg.header.type = StatusErr;
        msg.message = (void*)err;
    }
    return msg;
}

Message Messaging::MessageFromResults(void *results, size_t size)
{
    Message msg;
    msg.header = header_default;
    msg.header.messageSize = size;
    msg.header.type = Results;
    msg.message = results;
    
    return msg;
}




