#include "PostRequestHandler.h"

#include "glog/logging.h"

HTTP_SERVER::V2::PostRequestHandler::PostRequestHandler() {}

HTTP_SERVER::V2::PostRequestHandler::~PostRequestHandler() {}

void HTTP_SERVER::V2::PostRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                                        Poco::Net::HTTPServerResponse &response)
{
    LOG(INFO) << "Request POST Received!";
    std::istream& in = request.stream();
    int size = request.getContentLength();
    char buffer[size + 1];
    in.read(buffer, size);
    buffer[size] = '\0';
    if (in) {
        PLOG(INFO) << " => from client: (Size " << size << ") newline\n" << buffer << std::endl;
    }
    response.setContentType("text/txt");
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream& os = response.send();
    os << buffer << std::endl;
    LOG(INFO) << "buffer data -> " << buffer;
}
