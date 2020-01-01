#ifndef HTTP_SERVER_V2__SERVER_MANAGER__H
#define HTTP_SERVER_V2__SERVER_MANAGER__H

#include "Poco/ThreadPool.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServerParams.h"

namespace HTTP_SERVER {
namespace V2 {

class ServerManager {
public:
    ServerManager();
    ~ServerManager();
    void start_server();
    void stop_server();

private:
    Poco::Net::HTTPRequestHandlerFactory::Ptr factory_;
    Poco::Net::ServerSocket socket_;
    Poco::ThreadPool pool_;
    Poco::Net::HTTPServerParams::Ptr serverParams_;
    Poco::Net::HTTPServer server_;
};

}
}

#endif //HTTP_SERVER_V2__SERVER_MANAGER__H
