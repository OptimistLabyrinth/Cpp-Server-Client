#include <csignal>
#include <cstdlib>
#include "glog/logging.h"
#include "server_main/ServerManager.h"

HTTP_SERVER::V2::ServerManager* serverManagerPointer;

void atexit_handler();
void signal_handler(int sig);

int main() {
    FLAGS_minloglevel = google::GLOG_INFO;
    FLAGS_logtostderr = true;
    google::InitGoogleLogging("http_server_v2");
    std::atexit(google::ShutdownGoogleLogging);
    std::atexit(atexit_handler);
    std::signal(SIGINT ,signal_handler);
    std::signal(SIGTERM ,signal_handler);
#ifdef SIGQUIT
    std::signal(SIGQUIT ,signal_handler);
#endif

    HTTP_SERVER::V2::ServerManager serverManager;
    serverManagerPointer = &serverManager;
    serverManager.start_server();

    LOG(INFO) << "HTTP Server is Running...";
    while (true) {
        pause();
    }
    return 0;
}

void atexit_handler() {
    serverManagerPointer->stop_server();
}

void signal_handler(int sig) {
    std::exit(EXIT_SUCCESS);
}
