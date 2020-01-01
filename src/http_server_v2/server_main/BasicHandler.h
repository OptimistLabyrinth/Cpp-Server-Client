#ifndef HTTP_SERVER_V2__BASIC_HANDLER__H
#define HTTP_SERVER_V2__BASIC_HANDLER__H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace HTTP_SERVER {
namespace V2 {

class BasicHandler : public Poco::Net::HTTPRequestHandler {
public:
    BasicHandler();
    ~BasicHandler();
    virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
};

}
}

#endif //HTTP_SERVER_V2__BASIC_HANDLER__H
