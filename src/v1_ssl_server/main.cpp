#include <cstdlib>
#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/bind.hpp"
#include "glog/logging.h"

class Session {
public:
  Session(boost::asio::io_context& io_context, boost::asio::ssl::context& ssl_context)
  : ssl_socket_(io_context, ssl_context) {
  }
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& socket() {
    return ssl_socket_.lowest_layer();
  }
  void start() {
    LOG(INFO) << "connected: [" << ssl_socket_.lowest_layer().local_endpoint().address() 
      << ":" << ssl_socket_.lowest_layer().local_endpoint().port() << "] <->"
      << "[" << ssl_socket_.lowest_layer().remote_endpoint().address()
      << ":" << ssl_socket_.lowest_layer().remote_endpoint().port() << "]";
    ssl_socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&Session::handle_handshake, this, boost::asio::placeholders::error));
  }
  void handle_handshake(const boost::system::error_code& error) {
    if (! error) {
      LOG(INFO) << "handshake OK";
      ssl_socket_.async_read_some(boost::asio::buffer(read_data_, max_length),
          boost::bind(&Session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
      LOG(INFO) << "handshake Failed... " << error.message();
      delete this;
    }
  }
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (! error) {
      LOG(INFO) << "read OK [size: " << bytes_transferred << "]";
      LOG(INFO) << "         -> " << std::string(read_data_.begin(), read_data_.end());
      write_data_.clear();
      write_data_.resize(read_data_.size());
      write_data_.assign(read_data_.rbegin(), read_data_.rend());
      boost::asio::async_write(ssl_socket_, boost::asio::buffer(write_data_, bytes_transferred),
          boost::bind(&Session::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
      LOG(INFO) << "read Failed... " << error.message();
      delete this;
    }
  }
  void handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
    if (! error) {
      LOG(INFO) << "write OK [size: " << bytes_transferred << "]";
      LOG(INFO) << "         -> " << std::string(write_data_.begin(), write_data_.end());
      read_data_.clear();
      read_data_.resize(max_length);
      ssl_socket_.async_read_some(boost::asio::buffer(read_data_, max_length),
          boost::bind(&Session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
      LOG(INFO) << "write Failed... " << error.message();
      delete this;
    }
  }
private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket_;
  enum { max_length = 1024 };
  std::vector<char> read_data_;
  std::vector<char> write_data_;
};

class Server {
public:
  Server(boost::asio::io_context& io_context, unsigned short port)
  : io_context_(io_context)
  , acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
  , ssl_context_(boost::asio::ssl::context::sslv23)
  {
    ssl_context_.set_options(boost::asio::ssl::context::default_workarounds
      | boost::asio::ssl::context::no_sslv2
      | boost::asio::ssl::context::single_dh_use);
    ssl_context_.set_password_callback(boost::bind(&Server::get_password));
    ssl_context_.use_certificate_chain_file("/home/ksyoo/ksyooF/certificates/user.crt");
    ssl_context_.use_private_key_file("/home/ksyoo/ksyooF/certificates/user.key", boost::asio::ssl::context::pem);
    ssl_context_.use_tmp_dh_file("/home/ksyoo/ksyooF/certificates/dh2048.pem");

    start_accept();
  }
  static std::string get_password() {
    return "test";
  }
  void start_accept() {
    Session* new_session = new Session(io_context_, ssl_context_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
  }
  void handle_accept(Session* new_session, const boost::system::error_code& error) {
    LOG(INFO) << "New Client ! ! !";
    if (! error) {
      LOG(INFO) << "session successfully started...";
      new_session->start();
    } else {
      LOG(INFO) << "session failed to started... " << error.message();
      delete new_session;
    }
    start_accept();
  }
private:
  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ssl::context ssl_context_;
};

int main() {
    FLAGS_minloglevel = google::GLOG_INFO;
    FLAGS_logtostderr = true;
    google::InitGoogleLogging("v1_ssl_server");
    std::atexit(google::ShutdownGoogleLogging);

    boost::asio::io_context io_context;
    Server server(io_context, 5595);
    io_context.run();

    return 0;
}
