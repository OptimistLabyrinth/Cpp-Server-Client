#include "RequestHandler.h"

#include <cstring>
#include <fstream>
#include "boost/lexical_cast.hpp"
#include "MIME_TYPES.h"

HTTP_SERVER::V1::RequestHandler::RequestHandler(const std::string &doc_root) {

}

HTTP_SERVER::V1::RequestHandler::~RequestHandler() {}

void HTTP_SERVER::V1::RequestHandler::handle_request(const HTTP_SERVER::V1::Request &request,
                                                     HTTP_SERVER::V1::Reply &reply)
{
    // Decode url to path.
    std::string request_path;
    if (! url_decode(request.uri, request_path)) {
        reply = Reply::stock_reply(Reply::bad_request);
        return;
    }
    // Request path must be absolute and not contain "..".
    if (request_path.empty() || request_path[0] != '/'
        || request_path.find("..") != std::string::npos)
    {
        reply = Reply::stock_reply(Reply::bad_request);
        return;
    }
    // If path ends in slash (i.e. is a directory) then add "index.html".
    if (request_path[request_path.size() - 1] == '/') {
        request_path += "index.html";
    }
    // Determine the file extension.
    std::size_t last_slash_pos = request_path.find_last_of("/");
    std::size_t last_dot_pos = request_path.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
        extension = request_path.substr(last_dot_pos + 1);
    }
    // Open the file to send back.
    std::string full_path = doc_root_ + request_path;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        reply = Reply::stock_reply(Reply::not_found);
        return;
    }
    // Fill out the reply to be sent to the client.
    reply.status = Reply::ok;
    char buf[512];
    memset(buf, 0, sizeof(buf));
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        reply.content.append(buf, is.gcount());
    reply.headers.resize(2);
    reply.headers[0].name = "Content-Length";
    reply.headers[0].value = boost::lexical_cast<std::string>(reply.content.size());
    reply.headers[1].name = "Content-Type";
    reply.headers[1].value = MIME_TYPES::extension_to_type(extension);
}

// static private
bool HTTP_SERVER::V1::RequestHandler::url_decode(const std::string &in, std::string &out) {
    return false;
}
