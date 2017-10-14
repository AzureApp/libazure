#include "../tcp_server.h"

int main() {
    azure::TCPServer server("127.0.0.1", 1248);
    server.Setup();
    server.Run();
}