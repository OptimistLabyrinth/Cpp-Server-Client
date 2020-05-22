#ifndef CPP_SERVER_CLIENT__V2_MY_CLIENT_H
#define CPP_SERVER_CLIENT__V2_MY_CLIENT_H

#include <vector>
#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/bind.hpp"

namespace v2_ssl_client {
namespace client_internal {

class MyClient {
public:
  explicit MyClient(boost::asio::io_context& io_context, boost::asio::ssl::context& ssl_context);
  ~MyClient();

  void Initialize();
  void Start();
  void Finalize();

private:
  void OnResolve(const boost::system::error_code& error, const boost::asio::ip::tcp::resolver::results_type& endpoints);
  bool VerifyCallback(bool preverified, boost::asio::ssl::verify_context& ssl_context);
  void OnConnect(const boost::system::error_code& error);
  void OnHandshake(const boost::system::error_code& error);
  void OnWrite(const boost::system::error_code& error);
  void OnRead(const boost::system::error_code& error, const size_t bytes_transferred);

  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::resolver resolver_;
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  std::vector<char> write_buffer_;
  std::string write_data_;
  std::vector<char> read_buffer_;
  std::string read_data_;
};

}
}

#endif //CPP_SERVER_CLIENT__V2_MY_CLIENT_H
