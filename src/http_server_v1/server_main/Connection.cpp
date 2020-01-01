#include "Connection.h"

#include "boost/bind.hpp"
#include "glog/logging.h"

HTTP_SERVER::V1::Connection::Connection(
        boost::asio::io_context &io_context,
        HTTP_SERVER::V1::ConnectionManager& manager,
        RequestHandler &handler) :
    socket_(io_context)
    , connection_manager_(manager)
    , request_handler_(handler)
{
    start();
}

HTTP_SERVER::V1::Connection::~Connection() {}

boost::asio::ip::tcp::socket &HTTP_SERVER::V1::Connection::socket() {
    return socket_;
}

void HTTP_SERVER::V1::Connection::start() {
    socket_.async_receive(boost::asio::buffer(buffer_),
            boost::bind(
                    &Connection::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void HTTP_SERVER::V1::Connection::stop() {
    LOG(INFO) << "closed socket on ["
            << socket_.remote_endpoint().address() << ":"
            << socket_.remote_endpoint().port() << "]";
    socket_.close();
}

// private
void HTTP_SERVER::V1::Connection::handle_read(const boost::system::error_code &ec, size_t bytes_transferred) {
    if (! ec) {
        boost::tribool result;
        boost::tie(result, boost::tuples::ignore) =
                request_parser_.parse(request_, buffer_.data(), buffer_.data() + bytes_transferred);
        if (result) {
            request_handler_.handle_request(request_, reply_);
            socket_.async_send(reply_.to_buffers(),
                    boost::bind(&Connection::handle_write, shared_from_this(), boost::asio::placeholders::error));
        }
        else if (! result) {
            reply_ = Reply::stock_reply(Reply::bad_request);
            socket_.async_send(reply_.to_buffers(),
                    boost::bind(&Connection::handle_write, shared_from_this(), boost::asio::placeholders::error));
        }
        else {
            socket_.async_receive(boost::asio::buffer(buffer_),
                    boost::bind(
                            &Connection::handle_read,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
        }
    }
    else if (ec != boost::asio::error::operation_aborted) {
        connection_manager_.stop(shared_from_this());
    }
}

// private
void HTTP_SERVER::V1::Connection::handle_write(const boost::system::error_code &ec) {
    if (! ec) {
        // Initiate graceful connection closure.
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }
    else if (ec != boost::asio::error::operation_aborted) {
        connection_manager_.stop(shared_from_this());
    }
}
