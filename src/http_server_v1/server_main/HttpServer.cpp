#include "HttpServer.h"

#include "boost/bind.hpp"
#include "glog/logging.h"

HTTP_SERVER::V1::HttpServer::HttpServer() :
    acceptor_(io_context_)
    , signals_(io_context_)
    , connection_manager_()
    , new_connection_()
    , request_handler_(doc_root_)
{
    // Register to handle the signals that indicate when the server should exit.
    // It is safe to register for the same signal multiple times in a program,
    // provided all registration for the specified signal is made through Asio.
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
#if defined(SIGQUIT)
    signals_.add(SIGQUIT);
#endif
    signals_.async_wait(
            boost::bind(
                    &HttpServer::handle_stop,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::signal_number));

    // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
    boost::asio::ip::tcp::resolver resolver(io_context_);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address_, port_).begin();
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    start_accept();
}

HTTP_SERVER::V1::HttpServer::~HttpServer() {}

void HTTP_SERVER::V1::HttpServer::Run() {
    // The io_context::run() call will block until all asynchronous operations
    // have finished. While the server is running, there is always at least one
    // asynchronous operation outstanding: the asynchronous accept call waiting
    // for new incoming connections.
    io_context_.run();
}

// private
void HTTP_SERVER::V1::HttpServer::start_accept() {
    new_connection_.reset(new Connection(io_context_, connection_manager_, request_handler_));
    acceptor_.async_accept(new_connection_->socket(),
            boost::bind(&HttpServer::handle_accept, this, boost::asio::placeholders::error));
}

// private
void HTTP_SERVER::V1::HttpServer::handle_accept(const boost::system::error_code &ec) {
    // Check whether the server was stopped by a signal before this completion
    // handler had a chance to run.
    if (! acceptor_.is_open()) {
        PLOG(ERROR) << "cannot accept";
        return;
    }
    if (! ec) {
        connection_manager_.start(new_connection_);
    }
    else {
        PLOG(INFO) << "on accept error";
    }

    start_accept();
}

// private
void HTTP_SERVER::V1::HttpServer::handle_stop(const boost::system::error_code& ec, int sig) {
    // The server is stopped by cancelling all outstanding asynchronous
    // operations. Once all operations have finished the io_context::run() call
    // will exit.
    LOG(INFO) << "signal no." << sig << " occurred";
    acceptor_.close();
    connection_manager_.stop_all();
}
