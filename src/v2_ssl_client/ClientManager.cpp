#include "ClientManager.h"
#include "glog/logging.h"

v2_ssl_client::ClientManager::ClientManager()
  : io_context_()
  , ssl_context_(boost::asio::ssl::context::sslv23) {
}

v2_ssl_client::ClientManager::~ClientManager() {
  Finalize();
}

void v2_ssl_client::ClientManager::Initialize() {
  LOG(INFO) << "called ClientManager::Initialize()... loading verify file...";
  ssl_context_.load_verify_file("/home/ksyoo/ksyooF/certificates/rootca.crt");
  my_client_.reset(new client_internal::MyClient(io_context_, ssl_context_));
  my_client_->Initialize();
}

void v2_ssl_client::ClientManager::Start() {
  LOG(INFO) << "called ClientManager::Start()";
  my_client_->Start();
}

void v2_ssl_client::ClientManager::Finalize() {
  LOG(INFO) << "called ClientManager::Finalize()";
  my_client_->Finalize();
}
