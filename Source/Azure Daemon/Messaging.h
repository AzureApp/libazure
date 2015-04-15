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

    Message __attribute__((noinline)) SuccessMessage();
    Message __attribute__((noinline)) FailMessage(const char*);
    Message __attribute__((noinline)) MessageFromData(ResultsList *results, int start, int count);
    Message __attribute__((noinline)) MessageFromResults(ResultsList *results);
};

#endif /* defined(__Azure__Messaging__) */
