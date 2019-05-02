#include "connection_service.h"

namespace azure {

Status ConnectionServiceImpl::Connect(ServerContext* context,
                                      const proto::Handshake* request,
                                      proto::Handshake* response) {
  return Status(grpc::StatusCode::DO_NOT_USE, "Unimplemented");
}

Status ConnectionServiceImpl::Disconnect(
    ServerContext* context, const proto::DisconnectRequest* request,
    proto::DisconnectResponse* response) {
  return Status(grpc::StatusCode::DO_NOT_USE, "Unimplemented");
}

}  // namespace azure