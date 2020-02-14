#include <cstdlib>
#include "glog/logging.h"

int main() {
    FLAGS_minloglevel = google::GLOG_INFO;
    FLAGS_logtostderr = true;
    google::InitGoogleLogging("http_server_v1");
    std::atexit(google::ShutdownGoogleLogging);

    LOG(INFO) << "http server v1 START";

    return 0;
}
