#include <cstdlib>
#include "glog/logging.h"
#include "ServerManager.h"

int main() {
  FLAGS_minloglevel = google::GLOG_INFO;
  FLAGS_logtostderr = false;
  FLAGS_alsologtostderr = true;
  google::InitGoogleLogging("v2_ssl_server");
  std::atexit(google::ShutdownGoogleLogging);

  v2_ssl_server::ServerManager server_manager;
  server_manager.Initialize();
  server_manager.Start();
  server_manager.Finalize();

  return 0;
}
