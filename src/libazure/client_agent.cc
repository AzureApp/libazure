//
// Created by satori on 25/10/2017.
//

#include "client_agent.h"

#include "data_objects/meta_object.h"

#include "message_handlers/meta_handler.h"

namespace azure {

void ClientAgent::SpawnAgent(int client_fd) {
  ClientAgent agent(client_fd);
  agent.Run();
}

ClientAgent::ClientAgent(int client_fd) : conn_(client_fd), receiver_(&conn_) {
    message_handlers_ = {
            {MetaObject::Type::Meta, MetaHandler(this)}
    };
}

int ClientAgent::Run() {
    MetaObject object = receiver_.NextMessage();
    MessageHandler &handler = message_handlers_.find(object.type)->second;
    handler.HandleMessage(object);
}

}
