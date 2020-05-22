#ifndef CPP_SERVER_CLIENT__V2_CLIENT_MANAGER_H
#define CPP_SERVER_CLIENT__V2_CLIENT_MANAGER_H

#include "boost/shared_ptr.hpp"
#include "client_internal/MyClient.h"

namespace v2_ssl_client {

class ClientManager {
public:
  ClientManager();
  ~ClientManager();

  void Initialize();
  void Start();
  void Finalize();

private:
  boost::asio::io_context io_context_;
  boost::asio::ssl::context ssl_context_;
  boost::shared_ptr<client_internal::MyClient> my_client_;
};

}

#endif //CPP_SERVER_CLIENT__V2_CLIENT_MANAGER_H
