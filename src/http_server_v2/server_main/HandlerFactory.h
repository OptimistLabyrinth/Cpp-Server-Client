#ifndef HTTP_SERVER_V2__HANDLER_FACTORY__H
#define HTTP_SERVER_V2__HANDLER_FACTORY__H

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"

namespace HTTP_SERVER {
namespace V2 {

class HandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    HandlerFactory();
    virtual ~HandlerFactory();
    virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
};

}
}

#endif //HTTP_SERVER_V2__HANDLER_FACTORY__H
