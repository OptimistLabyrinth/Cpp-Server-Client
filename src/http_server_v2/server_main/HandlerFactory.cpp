#include "HandlerFactory.h"

#include "glog/logging.h"
#include "BasicHandler.h"
#include "PostRequestHandler.h"

HTTP_SERVER::V2::HandlerFactory::HandlerFactory() {}

HTTP_SERVER::V2::HandlerFactory::~HandlerFactory() {}


Poco::Net::HTTPRequestHandler* HTTP_SERVER::V2::HandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request)
{
    if(request.getMethod() == "GET") {
        return new HTTP_SERVER::V2::BasicHandler();
    } else {
        return new HTTP_SERVER::V2::PostRequestHandler();
    }
}
