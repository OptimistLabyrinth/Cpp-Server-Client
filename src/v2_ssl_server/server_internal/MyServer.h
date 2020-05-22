#ifndef CPP_SERVER_CLIENT__V2_MY_SERVER_H
#define CPP_SERVER_CLIENT__V2_MY_SERVER_H

#include <vector>
#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/bind.hpp"

namespace v2_ssl_server {
namespace server_internal {

class MyServer {
public:
  explicit MyServer(boost::asio::io_context& io_context, boost::asio::ssl::context& ssl_context);
  ~MyServer();

  void Initialize();
  void Start();
  void Finalize();

private:
  std::string PasswordCallback() const;
  void OnAccept(const boost::system::error_code& ec);
  void OnHandshake(const boost::system::error_code& ec);
  void OnRead(const boost::system::error_code& ec, const size_t bytes_transferred);
  void OnWrite(const boost::system::error_code& ec);

  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  std::vector<char> write_buffer_;
  std::string write_data_;
  std::vector<char> read_buffer_;
  std::string read_data_;
};

}
}

#endif //CPP_SERVER_CLIENT__V2_MY_SERVER_H
