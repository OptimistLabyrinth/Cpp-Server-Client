#include <cstdlib>
#include "glog/logging.h"
//#include "server_main/HttpServer.h"

int main() {
    FLAGS_minloglevel = google::GLOG_INFO;
    FLAGS_logtostderr = true;
    google::InitGoogleLogging("http_server_v1");
    std::atexit(google::ShutdownGoogleLogging);

//    HTTP_SERVER::V1::HttpServer httpServer;
//    httpServer.Run();

    return 0;
}
