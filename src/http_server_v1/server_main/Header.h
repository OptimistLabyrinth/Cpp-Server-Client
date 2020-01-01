#ifndef SERVER_CLIENT_HEADER_H
#define SERVER_CLIENT_HEADER_H

#include <string>

namespace HTTP_SERVER {
namespace V1 {

struct Header {
    std::string name;
    std::string value;
};

}
}

#endif //SERVER_CLIENT_HEADER_H
