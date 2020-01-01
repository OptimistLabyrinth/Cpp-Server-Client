#ifndef HTTP_SERVER_V1__CONNECTION_MANAGER__H
#define HTTP_SERVER_V1__CONNECTION_MANAGER__H

#include <set>
#include "Connection.h"

namespace HTTP_SERVER {
namespace V1 {

// Manages open connections so that they may be cleanly stopped when the server
// needs to shut down.
class ConnectionManager : private boost::noncopyable {
public:
    ConnectionManager();
    ~ConnectionManager();
    // Add the specified connection to the manager and start it
    void start(ConnectionPointer& connection);
    // Stop the specified connection.
    void stop(ConnectionPointer& connection);
    // Stop all connections.
    void stop_all();

private:
    // The managed connections.
    std::set<ConnectionPointer> connections_;
};

}
}

#endif //HTTP_SERVER_V1__CONNECTION_MANAGER__H
