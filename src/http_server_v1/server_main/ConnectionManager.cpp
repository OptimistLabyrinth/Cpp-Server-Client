#include "ConnectionManager.h"

#include <algorithm>
#include "boost/bind.hpp"

HTTP_SERVER::V1::ConnectionManager::ConnectionManager() {}

HTTP_SERVER::V1::ConnectionManager::~ConnectionManager() {}

void HTTP_SERVER::V1::ConnectionManager::start(ConnectionPointer &connection) {
    connections_.insert(connection);

}

void HTTP_SERVER::V1::ConnectionManager::stop(ConnectionPointer &connection) {
    connections_.erase(connection);

}

void HTTP_SERVER::V1::ConnectionManager::stop_all() {
    std::for_each(connections_.begin(), connections_.end(),
            boost::bind(&Connection::stop, boost::placeholders::_1));
    connections_.clear();
}
