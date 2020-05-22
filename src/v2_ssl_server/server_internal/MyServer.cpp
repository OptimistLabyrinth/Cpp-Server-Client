#include "MyServer.h"
#include "glog/logging.h"

v2_ssl_server::server_internal::MyServer::MyServer(boost::asio::io_context &io_context, boost::asio::ssl::context &ssl_context)
  : io_context_(io_context)
  , socket_(io_context, ssl_context)
  , acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9797)) {
}

v2_ssl_server::server_internal::MyServer::~MyServer() {
  Finalize();
}

void v2_ssl_server::server_internal::MyServer::Initialize() {
  LOG(INFO) << "Server Initialize";
  acceptor_.async_accept(socket_.lowest_layer(),
      boost::bind(&MyServer::OnAccept, this, boost::asio::placeholders::error));
}

void v2_ssl_server::server_internal::MyServer::Start() {
  LOG(INFO) << "Server Start";
  io_context_.run();
}

void v2_ssl_server::server_internal::MyServer::Finalize() {
  LOG(INFO) << "Server Finalize";
  if (! io_context_.stopped()) {
    io_context_.stop();
    LOG(INFO) << "Server stopped io_context";
  }
}

std::string v2_ssl_server::server_internal::MyServer::PasswordCallback() const {
  return "test";
}

void v2_ssl_server::server_internal::MyServer::OnAccept(const boost::system::error_code &ec) {
  if (! ec) {
    LOG(INFO) << "Server OnAccept Success";
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&MyServer::OnHandshake, this, boost::asio::placeholders::error));
  } else {
    PLOG(INFO) << "Server OnAccept Failure " << ec.message();
  }
}

void v2_ssl_server::server_internal::MyServer::OnHandshake(const boost::system::error_code &ec) {
  if (! ec) {
    LOG(INFO) << "Server OnHandshake Success";
    read_buffer_.resize(1024);
    socket_.async_read_some(boost::asio::buffer(read_buffer_, 1024),
        boost::bind(&MyServer::OnRead, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  } else {
    PLOG(INFO) << "Server OnHandshake Failure " << ec.message();
  }
}

void v2_ssl_server::server_internal::MyServer::OnRead(const boost::system::error_code &ec, const size_t bytes_transferred) {
  if (! ec) {
    read_data_.assign(read_buffer_.begin(), read_buffer_.end());
    LOG(INFO) << "Server OnRead Success (from Client: " << read_data_ << ")";
    write_data_.assign("Reply from server to client");
    write_buffer_.assign(write_data_.begin(), write_data_.end());
    boost::asio::async_write(socket_, boost::asio::buffer(write_buffer_, 1024),
        boost::bind(&MyServer::OnWrite, this, boost::asio::placeholders::error));
  } else {
    PLOG(INFO) << "Server OnRead Failure" << ec.message();
  }
}

void v2_ssl_server::server_internal::MyServer::OnWrite(const boost::system::error_code &ec) {
  if (! ec) {
    LOG(INFO) << "Server OnWrite Success";
  } else {
    PLOG(INFO) << "Server OnWrite Failure " << ec.message();
  }
}
