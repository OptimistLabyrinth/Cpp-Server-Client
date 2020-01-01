#ifndef HTTP_SERVER_V1__REQUEST__H
#define HTTP_SERVER_V1__REQUEST__H

#include <vector>
#include "Header.h"

namespace HTTP_SERVER {
namespace V1 {

struct Request {
    Request();

    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
};

}
}

#endif //HTTP_SERVER_V1__REQUEST__H
