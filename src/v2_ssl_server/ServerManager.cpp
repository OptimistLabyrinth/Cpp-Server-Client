#include "ServerManager.h"
#include "glog/logging.h"

v2_ssl_server::ServerManager::ServerManager()
  : io_context_()
  , ssl_context_(boost::asio::ssl::context::sslv23) {
}

v2_ssl_server::ServerManager::~ServerManager() {
  Finalize();
}

void v2_ssl_server::ServerManager::Initialize() {
  LOG(INFO) << "called ServerManager::Initialize()... loading certificate files to ssl context...";
  ssl_context_.set_options(boost::asio::ssl::context::default_workarounds
      | boost::asio::ssl::context::no_sslv2
      | boost::asio::ssl::context::single_dh_use);
  ssl_context_.set_password_callback(boost::bind(&ServerManager::GetPassword, this));
  ssl_context_.use_certificate_chain_file("/home/ksyoo/ksyooF/certificates/user.crt");
  ssl_context_.use_private_key_file("/home/ksyoo/ksyooF/certificates/user.key", boost::asio::ssl::context::pem);
  ssl_context_.use_tmp_dh_file("/home/ksyoo/ksyooF/certificates/dh2048.pem");
  my_server_.reset(new server_internal::MyServer(io_context_, ssl_context_));
  my_server_->Initialize();
}

void v2_ssl_server::ServerManager::Start() {
  LOG(INFO) << "called ServerManager::Start()";
  my_server_->Start();
}

void v2_ssl_server::ServerManager::Finalize() {
  LOG(INFO) << "called ServerManager::Finalize()";
  my_server_->Finalize();
}

std::string v2_ssl_server::ServerManager::GetPassword() const {
  return "";
}
