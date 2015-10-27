#include <mutex>
#include <memory>
#include <ebbrt/Net.h>
#include <ebbrt/NetTcpHandler.h>
#include <ebbrt/StaticSharedEbb.h>
#include <ebbrt/SharedIOBufRef.h>
//
namespace ebbrt {
class IOStreamHandler : public ebbrt::TcpHandler  {
public:
    IOStreamHandler(ebbrt::NetworkManager::TcpPcb pcb)
      : ebbrt::TcpHandler(std::move(pcb)) {}
    void Abort() override {}
    void Close() override { Shutdown(); }
    //void Send()  override {}
    void Receive(std::unique_ptr<MutIOBuf> b) override;
  };
}//end ebbrt namespace
