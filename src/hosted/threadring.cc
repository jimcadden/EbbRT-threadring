//          Copyright Boston University SESA Group 2013 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <signal.h>

#include <boost/filesystem.hpp>

#include <ebbrt/Cpu.h>
#include <ebbrt/EventManager.h>
#include <ebbrt/hosted/NodeAllocator.h>

#include "../ThreadRing.h"

static char* ExecName = 0;

void AppMain() {
  auto bindir = boost::filesystem::system_complete(ExecName).parent_path() /
                "/bm/threadring.elf32";

	std::cout << "Got to AppMain! " << std::endl;
  auto id = ebbrt::GenerateStaticEbbId("ThreadRingId");
  auto tr = new ThreadRingMember(id);
  ThreadRingMember::Create(tr,id); 
  tring->Init(); 
  ebbrt::event_manager->Spawn([bindir]() {
    try {
      ebbrt::node_allocator->AllocateNode(bindir.string());
    } catch (std::runtime_error &e) {
      std::cout << e.what() << std::endl;
      exit(1);
    }
  });
  ebbrt::event_manager->Spawn([bindir]() {
    try {
      ebbrt::node_allocator->AllocateNode(bindir.string());
    } catch (std::runtime_error &e) {
      std::cout << e.what() << std::endl;
      exit(1);
    }
  });
}

int main(int argc, char **argv) {
  void *status;

  ExecName = argv[0];

  pthread_t tid = ebbrt::Cpu::EarlyInit(1);

  pthread_join(tid, &status);

  return 0;
}
