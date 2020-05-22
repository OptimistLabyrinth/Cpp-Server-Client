#ifndef CPP_SERVER_CLIENT_SERVERMANAGER_H
#define CPP_SERVER_CLIENT_SERVERMANAGER_H

#include "boost/shared_ptr.hpp"
#include "server_internal/MyServer.h"

namespace v2_ssl_server {

class ServerManager {
public:
  ServerManager();
  ~ServerManager();

  void Initialize();
  void Start();
  void Finalize();

private:
  std::string GetPassword() const;

  boost::asio::io_context io_context_;
  boost::asio::ssl::context ssl_context_;
  boost::shared_ptr<server_internal::MyServer> my_server_;
};

}

#endif //CPP_SERVER_CLIENT_SERVERMANAGER_H
