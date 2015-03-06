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



class Messaging {
public:
    Messaging();
    ~Messaging();
    static Messaging* GetInstance();
    
    kern_return_t Tick();
    
    kern_return_t ProcessMessage(Message &);
    
    void PushMessage(Message &);
    void PopMessage(int);
    
private:
    static Message SuccessMessage();
    static Message FailMessage(const char*);
    static Message MessageFromResults(void *, size_t);
    std::vector<Message> messageStack;
};

#endif /* defined(__Azure__Messaging__) */
