#ifndef HTTP_SERVER_V2__POST_REQUEST_HANDLER__H
#define HTTP_SERVER_V2__POST_REQUEST_HANDLER__H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace HTTP_SERVER {
namespace V2 {

class PostRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    PostRequestHandler();
    ~PostRequestHandler();
    virtual void handleRequest( Poco::Net::HTTPServerRequest & request,
                                Poco::Net::HTTPServerResponse & response);

private:
};

}
}

#endif //HTTP_SERVER_V2__POST_REQUEST_HANDLER__H
