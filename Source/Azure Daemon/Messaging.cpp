//
//  Messaging.cpp
//  Azure
//
//  Created by callum taylor on 25/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "Messaging.h"
#include "Azure.h"

AZ_STATUS Messaging::ProcessMessage(Message& message) // maybe need to free message.message after use?
{
    Azure *azure = Azure::GetInstance();
    MemoryManager *manager = MemoryManager::GetInstance();
    if (messageIsValid(message)) {
        switch (message.header.type) {
                
            case StatusOK:
            case StatusErr:
                return AZ_SUCCESS; // not really useful
                
            case Attach:
            {
                msg_process *procData = (msg_process*)message.message;
                Process *proc = new Process(procData);
                AZ_STATUS status = ProcessUtils::TryAttach(proc);
                AZLog("DEBUG: TryAttach returned %s", mach_error_string(status));
                if (status == AZ_SUCCESS)
                {
                    azure->AttachToProcess(proc);
                    message = SuccessMessage();
                }
                else
                {
                    message = FailMessage(NULL);
                }
                return status;
            }
            case Detach:
                // TODO
                break;
                
            case NewSearch:
            {
                manager->ResetResults();
                void *pattern = message.message;
                size_t size = message.header.messageSize;
                AZLog("pattern = %x, size = %d", *(int*)pattern, size);
                
                AZ_STATUS status = manager->Find(pattern, size);
                if (status != AZ_SUCCESS)
                {
                    AZLog("an error has occured finding addresses: %s", mach_error_string(status));
                }
                AddressList *addresses = manager->Results();
                AZLog("found %d results", addresses->size());
                message = MessageFromResults(addresses->data(), addresses->size()*sizeof(vm_address_t));
                
                return AZ_SUCCESS;
            }
                
            case IterateSearch:
            {
                void *pattern = message.message;
                size_t size = message.header.messageSize;
                AZ_STATUS status = manager->Iterate(pattern, size, manager->Results());
                if (status != AZ_SUCCESS)
                {
                    AZLog("an error has occured finding addresses: %s", mach_error_string(status));
                }
                AddressList *addresses = manager->Results();
                AZLog("found %d results", addresses->size());
                message = MessageFromResults(addresses->data(), addresses->size()*sizeof(vm_address_t));
                
                return AZ_SUCCESS;
            }
            case Edit:
                
                break;
            case Lock:
                
                break;

        }
    }
    return AZ_FAILURE;
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
