#ifndef HTTP_SERVER_V1__CONNECTION__H
#define HTTP_SERVER_V1__CONNECTION__H

#include "boost/enable_shared_from_this.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/system/error_code.hpp"
#include "ConnectionManager.h"
#include "RequestHandler.h"
#include "RequestParser.h"

namespace HTTP_SERVER {
namespace V1 {

class ConnectionManager;

// Represents a single connection from a client.
class Connection :
        public boost::enable_shared_from_this<Connection>
        , private boost::noncopyable
{
public:
    // Construct a connection with the given io_context.
    Connection(boost::asio::io_context& io_context, ConnectionManager& manager, RequestHandler& handler);
    ~Connection();
    // Get the socket associated with the connection.
    boost::asio::ip::tcp::socket& socket();
    // Start the first asynchronous operation for the connection.
    void start();
    // Stop all asynchronous operations associated with the connection.
    void stop();

private:
    // Handle completion of a read operation.
    void handle_read(const boost::system::error_code& ec, size_t bytes_transferred);
    // Handle completion of a write operation.
    void handle_write(const boost::system::error_code& ec);

    // Socket for the connection.
    boost::asio::ip::tcp::socket socket_;
    // The manager for this connection.
    ConnectionManager& connection_manager_;
    // The handler used to process the incoming request.
    RequestHandler& request_handler_;
    // Buffer for incoming data.
    std::vector<char> buffer_;
    // The incoming request.
    Request request_;
    // The parser for the incoming request.
    RequestParser request_parser_;
    // The reply to be sent back to the client.
    Reply reply_;
};

typedef boost::shared_ptr<Connection> ConnectionPointer;

}
}

#endif //HTTP_SERVER_V1__CONNECTION__H
