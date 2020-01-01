#include "BasicHandler.h"

#include "glog/logging.h"

HTTP_SERVER::V2::BasicHandler::BasicHandler() {

}

HTTP_SERVER::V2::BasicHandler::~BasicHandler() {

}

void HTTP_SERVER::V2::BasicHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                                  Poco::Net::HTTPServerResponse &response)
{
    LOG(INFO) << "Received GET Request";
    LOG(INFO) << "URI : " << request.getURI();
//    {
//        std::ostringstream os;
//        request.write(os);
//        LOG(INFO) << "=>newline\n" << os.str();
//    }
    response.setContentType("text/txt");
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream& os = response.send();
    os << "Server reponse" << std::endl;
    LOG(INFO) << "Server reponse";
}
