//
// Created by satori on 25/10/2017.
//

#ifndef AZURE_CLIENT_AGENT_H
#define AZURE_CLIENT_AGENT_H

#include "tcp_conn.h"
#include "message_receiver.h"
#include "message_handler.h"

namespace azure {

using MessageHandlerPair = std::map<MetaObject::Type, MessageHandler>;

/**
 * Each client agent represents one connection to a client
 */
class ClientAgent {
public:
    ClientAgent(int client_fd);

    int Run();
private:
    TCPConn conn_;
    MessageReceiver receiver_;
    MessageHandlerPair message_handlers_;
};

}

#endif //AZURE_CLIENT_AGENT_H
