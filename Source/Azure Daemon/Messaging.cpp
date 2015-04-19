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
            case Results:
                return AZ_SUCCESS; // not really useful
                
            case Attach:
            {
                azure->DetachFromProcess();
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
            {
                azure->DetachFromProcess();
                
                message = SuccessMessage();
                return AZ_SUCCESS;
            }
                
            case NewSearch:
            {
                manager->ResetResults();
                SearchSettings *settings = (SearchSettings *)message.message;
                AZLog("settings type %d, data type %d, data value %d", settings->fuzzySettings, settings->searchObj.dataType, *(int*)settings->searchObj.data);
                AZ_STATUS status = manager->Find(*settings);
                if (status != AZ_SUCCESS)
                {
                    AZLog("an error has occured finding addresses: %s", mach_error_string(status));
                }
                AZLog("found %d addresses", manager->Results()->size());
                message = MessageFromResults(manager->Results());
                
                return AZ_SUCCESS;
            }
                
            case IterateSearch:
            {
                SearchSettings *settings = (SearchSettings *)message.message;
                
                AZ_STATUS status = manager->Iterate(*settings);
                if (status != AZ_SUCCESS)
                {
                    AZLog("an error has occured finding addresses: %s", mach_error_string(status));
                }
                AZLog("found %d addresses", manager->Results()->size());
                message = MessageFromResults(manager->Results());
                
                return AZ_SUCCESS;
            }
                
            case Values:
            {
                msg_values vals = *(msg_values*)message.message;
                AZ_STATUS status = manager->FetchUpdatedResults(vals.start, vals.count);
                if (status != AZ_SUCCESS)
                {
                    AZLog("an error has occured updating results: %s", mach_error_string(status));
                }
                ResultsList *results = manager->Results();
                AZLog("found %d values", results->size());
                message = MessageFromData(results, vals.start, vals.count);
                
                return AZ_SUCCESS;
            }
            case Edit:
            {
                DataObject *obj = (DataObject *)message.message;
                AZ_STATUS status = manager->Write(*obj);
                if (status != AZ_SUCCESS)
                {
                    AZLog("failed to write to address 0x%x", obj->address);
                }
                
                message = SuccessMessage();
                return AZ_SUCCESS;
            }

            case Lock:
            {
                DataObject *obj = (DataObject *)message.message;
                manager->Lock(*obj);
                
                message = SuccessMessage();
                return AZ_SUCCESS;
            }
            case Clear:
            {
                manager->ResetResults();
                message = MessageFromData(manager->Results(), 0, 0);
                return AZ_SUCCESS;
            }
            case Prefs:
            {
                //azure->GetSettings()->LoadSettings();
                return AZ_SUCCESS;
            }
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

Message Messaging::MessageFromData(ResultsList *results, int start, int count)
{
    Message msg;
    msg.header = header_default;
    msg.header.type = Values;
    msg.header.messageSize = count*sizeof(DataObject);
    msg.message = results->data()+start;
    
    return msg;
}

Message Messaging::MessageFromResults(ResultsList *results)
{
    Message msg;
    msg.header = header_default;
    msg.header.type = Results;
    msg.header.messageSize = sizeof(vm_address_t);
    
    vm_address_t *count = new vm_address_t;
    *count = results->size();
    msg.message = count;
    
    return msg;
}
