#ifndef HTTP_SERVER_V1__HTTP_SERVER__H
#define HTTP_SERVER_V1__HTTP_SERVER__H

#include "ConnectionManager.h"

namespace HTTP_SERVER {
namespace V1 {

class HttpServer : private boost::noncopyable {
public:
    // Construct the server to listen on the specified TCP address and port, and
    // serve up files from the given directory.
    HttpServer();
    ~HttpServer();
    // Run the server's io_context loop.
    void Run();

private:
    // Initiate an asynchronous accept operation.
    void start_accept();
    // Handle completion of an asynchronous accept operation.
    void handle_accept(const boost::system::error_code& ec);
    // Handle a request to stop the server.
    void handle_stop(const boost::system::error_code& ec, int sig);

    std::string address_;
    std::string port_;
    std::string doc_root_;
    // The io_context used to perform asynchronous operations.
    boost::asio::io_context io_context_;
    // Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor acceptor_;
    // The signal_set is used to register for process termination notifications.
    boost::asio::signal_set signals_;
    // The connection manager which owns all live connections.
    ConnectionManager connection_manager_;
    // The next connection to be accepted.
    ConnectionPointer new_connection_;
    // The handler for all incoming requests.
    RequestHandler request_handler_;
};

}
}

#endif //HTTP_SERVER_V1__HTTP_SERVER__H
