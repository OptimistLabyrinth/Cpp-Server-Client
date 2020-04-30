#include <cstdlib>
#include <iostream>
#include "boost/asio.hpp"
#include "boost/asio/ssl.hpp"
#include "boost/bind.hpp"
#include "glog/logging.h"

enum { max_length = 1024 };

class Client {
public:
  Client(boost::asio::io_context& io_context, boost::asio::ssl::context& context, boost::asio::ip::tcp::resolver::results_type endpoints)
  : request_count(0)
  , ssl_socket_(io_context, context)
  {
    ssl_socket_.set_verify_mode(boost::asio::ssl::verify_peer | boost::asio::ssl::verify_fail_if_no_peer_cert);
    ssl_socket_.set_verify_callback(boost::bind(&Client::verify_certificate, this, _1, _2));
    
    boost::asio::async_connect(ssl_socket_.lowest_layer(), endpoints,
        boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error));
  }
  bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& context) {
    char subject_name[256];
    memset(subject_name, 0, sizeof(subject_name));
    X509* cert = X509_STORE_CTX_get_current_cert(context.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 255);
    LOG(INFO) << "Verifying " << subject_name;
    
    return preverified;
  }
  void handle_connect(const boost::system::error_code& error) {
    if (!error) {
      LOG(INFO) << "connected: [" << ssl_socket_.lowest_layer().local_endpoint().address()
        << ":" << ssl_socket_.lowest_layer().local_endpoint().port() << "] <->"
        << "[" << ssl_socket_.lowest_layer().remote_endpoint().address()
        << ":" << ssl_socket_.lowest_layer().remote_endpoint().port() << "]";
      ssl_socket_.async_handshake(boost::asio::ssl::stream_base::client,
          boost::bind(&Client::handle_handshake, this, boost::asio::placeholders::error));
    } else {
      LOG(INFO) << "cannot connect to server..." << error.message();
    }
  }
  void handle_handshake(const boost::system::error_code& error) {
    if (!error) {
      std::cout << "Enter message 0: ";
      std::string buf;
      std::getline(std::cin, buf);
      request_.clear();
      request_.resize(buf.size());
      request_.assign(buf.begin(), buf.end());
      boost::asio::async_write(ssl_socket_, boost::asio::buffer(request_, request_.size()),
          boost::bind(&Client::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
      LOG(INFO) << "handshake failed..." << error.message();
    }
  }
  void handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
      LOG(INFO) << "Write OK [size: " << bytes_transferred << "]";
      reply_.clear();
      reply_.resize(max_length);
      ssl_socket_.async_read_some(boost::asio::buffer(reply_, bytes_transferred),
          boost::bind(&Client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
      LOG(ERROR) << "Write failed (count: " << request_count << ")... " << error.message();
    }
  }
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
      std::cout << "Enter message "<< ++request_count <<": ";
      std::string buf;
      std::getline(std::cin, buf);
      request_.clear();
      request_.resize(buf.size());
      request_.assign(buf.begin(), buf.end());
      boost::asio::async_write(ssl_socket_, boost::asio::buffer(request_, request_.size()),
          boost::bind(&Client::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
      LOG(ERROR) << "Read failed (count: " << request_count << ")... " << error.message();
    }
  }
private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket_;
  unsigned int request_count;
  std::vector<char> request_;
  std::vector<char> reply_;
};

int main() {
  FLAGS_minloglevel = google::GLOG_INFO;
  FLAGS_logtostderr = true;
  google::InitGoogleLogging("v1_ssl_client");
  std::atexit(google::ShutdownGoogleLogging);
  
  boost::asio::io_context io_context;
  boost::asio::ip::tcp::resolver resolver(io_context);
  boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "5595");
  boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
  ssl_context.load_verify_file("/home/ksyoo/ksyooF/certificates/rootca.crt");
  Client client(io_context, ssl_context, endpoints);
  io_context.run();
  
  return 0;
}
