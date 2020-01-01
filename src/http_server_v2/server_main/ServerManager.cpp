#include "ServerManager.h"

#include "HandlerFactory.h"

HTTP_SERVER::V2::ServerManager::ServerManager() :
    factory_(new HandlerFactory())
    , socket_(9691)
    , serverParams_(new Poco::Net::HTTPServerParams())
    , server_(factory_, pool_, socket_, serverParams_)
{}

HTTP_SERVER::V2::ServerManager::~ServerManager() {
    stop_server();
}

void HTTP_SERVER::V2::ServerManager::start_server() {
    server_.start();
}

void HTTP_SERVER::V2::ServerManager::stop_server() {
    server_.stop();
}
