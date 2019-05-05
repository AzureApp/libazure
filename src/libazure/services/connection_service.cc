#include "connection_service.h"
#include <iostream>
namespace azure {

Status ConnectionServiceImpl::Connect(ServerContext* context,
                                      const proto::Handshake* request,
                                      proto::Handshake* response) {
  const proto::DeviceInfo& info = request->device_info();
  std::cout << "Azure version: " << request->azure_version() << std::endl;
  std::cout << "Device Info"
            << "\n\t Operating System (value): " << info.operating_system()
            << "\n\t OS Version: " << info.os_version()
            << "\n\t Device name: " << info.device_name()
            << "\n\t UDID: " << info.udid();

  return Status(grpc::StatusCode::DO_NOT_USE, "Unimplemented");
}

Status ConnectionServiceImpl::Disconnect(
    ServerContext* context, const proto::DisconnectRequest* request,
    proto::DisconnectResponse* response) {
  return Status(grpc::StatusCode::DO_NOT_USE, "Unimplemented");
}

}  // namespace azure