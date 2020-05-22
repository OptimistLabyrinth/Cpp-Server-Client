#include "MyClient.h"
#include "glog/logging.h"

v2_ssl_client::client_internal::MyClient::MyClient(boost::asio::io_context& io_context, boost::asio::ssl::context& ssl_context)
  : io_context_(io_context)
  , socket_(io_context_, ssl_context)
  , resolver_(io_context) {
}

v2_ssl_client::client_internal::MyClient::~MyClient() {
  Finalize();
}

void v2_ssl_client::client_internal::MyClient::Initialize() {
  LOG(INFO) << "Client Initialize";
  resolver_.async_resolve(
      boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 9797),
      boost::bind(&MyClient::OnResolve, this,
          boost::asio::placeholders::error, boost::asio::placeholders::results));
}

void v2_ssl_client::client_internal::MyClient::Start() {
  LOG(INFO) << "Client Start";
  io_context_.run();
}

void v2_ssl_client::client_internal::MyClient::Finalize() {
  LOG(INFO) << "Client Finalize";
  if (! io_context_.stopped()) {
    io_context_.stop();
    LOG(INFO) << "Client stopped io_context";
  }
}

void v2_ssl_client::client_internal::MyClient::OnResolve(
    const boost::system::error_code& error, const boost::asio::ip::tcp::resolver::results_type& endpoints) {
  if (! error) {
    LOG(INFO) << "Client OnResolve Success";
    socket_.set_verify_mode(boost::asio::ssl::verify_peer);
    socket_.set_verify_callback(boost::bind(&MyClient::VerifyCallback, this, _1, _2));
    boost::asio::async_connect(socket_.lowest_layer(), endpoints,
        boost::bind(&MyClient::OnConnect, this, boost::asio::placeholders::error));
  } else {
    PLOG(INFO) << "Client OnResolve Failure " << error.message();
  }
}

bool v2_ssl_client::client_internal::MyClient::VerifyCallback(bool preverified, boost::asio::ssl::verify_context& ssl_context) {
//  char subject_name[256];
//  memset(subject_name, 0, sizeof(subject_name));
//  X509* cert = X509_STORE_CTX_get_current_cert(ssl_context.native_handle());
//  X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
//  LOG(INFO) << "Verifying " << subject_name << "\n";
  return preverified;
}

void v2_ssl_client::client_internal::MyClient::OnConnect(const boost::system::error_code& error) {
  if (! error) {
    LOG(INFO) << "Client OnConnect Success";
    socket_.async_handshake(boost::asio::ssl::stream_base::client,
        boost::bind(&MyClient::OnHandshake, this, boost::asio::placeholders::error));
  } else {
    PLOG(INFO) << "Client OnConnect Failure " << error.message();
  }
}

void v2_ssl_client::client_internal::MyClient::OnHandshake(const boost::system::error_code& error) {
  if (! error) {
    LOG(INFO) << "Client OnHandshake Success";
    write_data_.assign("Greeting from client to server");
    write_buffer_.assign(write_data_.begin(), write_data_.end());
    boost::asio::async_write(socket_, boost::asio::buffer(write_buffer_, 1024),
        boost::bind(&MyClient::OnWrite, this, boost::asio::placeholders::error));
  } else {
    PLOG(INFO) << "Client OnHandshake Failure " << error.message();
  }
}

void v2_ssl_client::client_internal::MyClient::OnWrite(const boost::system::error_code& error) {
  if (! error) {
    LOG(INFO) << "Client OnWrite Success";
    read_buffer_.resize(1024);
    socket_.async_read_some(boost::asio::buffer(read_buffer_, 1024),
        boost::bind(&MyClient::OnRead, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  } else {
    PLOG(INFO) << "Client OnWrite Failure " << error.message();
  }
}

void v2_ssl_client::client_internal::MyClient::OnRead(const boost::system::error_code& error, const size_t bytes_transferred) {
  if (! error) {
    read_data_.assign(read_buffer_.begin(), read_buffer_.end());
    LOG(INFO) << "Client OnRead Success (from Server: " << read_data_ << ")";
  } else {
    PLOG(INFO) << "Client OnRead Failure " << error.message();
  }
}
