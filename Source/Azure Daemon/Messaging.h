//
//  Messaging.h
//  Azure
//
//  Created by callum taylor on 25/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef __Azure__Messaging__
#define __Azure__Messaging__

#include <iostream>
#include <vector>

#include "MemoryManager.h"
#include "Message.h"

namespace Messaging {
    AZ_STATUS ProcessMessage(Message &);

    static Message SuccessMessage();
    static Message FailMessage(const char*);
    static Message MessageFromResults(void * ptr, size_t size);
};

#endif /* defined(__Azure__Messaging__) */
