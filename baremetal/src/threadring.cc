//          Copyright Boston University SESA Group 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <ebbrt/Net.h>
#include <ebbrt/NetTcpHandler.h>
#include "IOStreamHandler.h"

ebbrt::NetworkManager::ListeningTcpPcb listening_pcb;

void AppMain() {
  auto port = listening_pcb.Bind(0, [](ebbrt::NetworkManager::TcpPcb pcb) {
    // new connection callback
    ebbrt::kprintf("New Connection.\n");
    auto connection = new ebbrt::IOStreamHandler(std::move(pcb));
    connection->Install();
  });
  ebbrt::kprintf("Listening on port %u \n", port);
}
