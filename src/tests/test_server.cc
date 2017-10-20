#include "../libazure/tcp_server.h"

int main() {
    azure::TCPServer server("127.0.0.1", 1248);
    if (!server.Setup()) return 1;
    server.Run();
}
