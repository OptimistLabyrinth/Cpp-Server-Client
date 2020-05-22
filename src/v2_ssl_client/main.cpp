#include <cstdlib>
#include "glog/logging.h"
#include "ClientManager.h"

int main() {
  FLAGS_minloglevel = google::GLOG_INFO;
  FLAGS_logtostderr = false;
  FLAGS_alsologtostderr = true;
  google::InitGoogleLogging("v2_ssl_client");
  std::atexit(google::ShutdownGoogleLogging);

  v2_ssl_client::ClientManager client_manager;
  client_manager.Initialize();
  client_manager.Start();
  client_manager.Finalize();

  return 0;
}
