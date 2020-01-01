#ifndef HTTP_SERVER_V1__REQUEST_HANDLER__H
#define HTTP_SERVER_V1__REQUEST_HANDLER__H

#include "boost/noncopyable.hpp"
#include "Request.h"
#include "Reply.h"

namespace HTTP_SERVER {
namespace V1 {

struct Reply;
struct Request;

// The common handler for all incoming requests.
class RequestHandler : private boost::noncopyable {
public:
    // Construct with a directory containing files to be served.
    explicit RequestHandler(const std::string& doc_root);
    ~RequestHandler();
    // Handle a request and produce a reply.
    void handle_request(const Request& request, Reply& reply);

private:
    // Perform URL-decoding on a string. Returns false if the encoding was
    // invalid.
    static bool url_decode(const std::string& in, std::string& out);

    // The directory containing the files to be served.
    std::string doc_root_;
};

}
}

#endif //HTTP_SERVER_V1__REQUEST_HANDLER__H
