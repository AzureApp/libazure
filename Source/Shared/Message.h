//
//  Header.h
//  Azure
//
//  Created by callum taylor on 17/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef Server_Test_Header_h
#define Server_Test_Header_h

#include <sys/types.h>
#include <stdbool.h>
#include "Status.h"

#define DAEMON_PORT 1248
#define CHUNK_SIZE 16384

#define MSG_MAGIC 0xABAD1DEA // dedicated to my favorite virus

enum MessageType {
    StatusOK,
    StatusErr,
    Attach,
    Detach,
    NewSearch,
    IterateSearch,
    Edit,
    Lock,
    Results,
    Values,
    Clear,
    Prefs
};

struct msg_header {
    uint magic; // used to verify messages integrity
    enum MessageType type;
    size_t messageSize;
    bool shouldPop;
} static header_default = {MSG_MAGIC, StatusOK, 0, true};

struct Message {
    struct msg_header header;
    void *message;
};
typedef struct Message Message;

struct msg_process {
    pid_t pid;
    char *name;
};

struct msg_values {
    int start;
    int count;
};
typedef struct msg_values msg_values;

#if defined __cplusplus
extern "C" {
#endif
    
const char* enumToName(enum MessageType);
bool messageIsValid(struct Message);
    
#if defined __cplusplus
};
#endif

#endif
