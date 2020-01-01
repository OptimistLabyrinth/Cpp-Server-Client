#ifndef SERVER_CLIENT_MIME_TYPES_H
#define SERVER_CLIENT_MIME_TYPES_H

#include <string>

namespace HTTP_SERVER {
namespace V1 {
namespace MIME_TYPES {
    // Convert a file extension into a MIME type.
    std::string extension_to_type(const std::string& extension);
};
}
}

#endif //SERVER_CLIENT_MIME_TYPES_H
