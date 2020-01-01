#include <cstdlib>
#include "glog/logging.h"

int main() {
    FLAGS_minloglevel = google::GLOG_INFO;
    FLAGS_logtostderr = true;
    google::InitGoogleLogging("test_features");
    std::atexit(google::ShutdownGoogleLogging);

    LOG(INFO) << "test_features main()";

    return 0;
}
