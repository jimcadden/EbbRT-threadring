//          Copyright Boston University SESA Group 2013 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "../ThreadRing.h"
#include <ebbrt/GlobalStaticIds.h>
#include <ebbrt/EventManager.h>

void AppMain() { 

  ebbrt::kprintf("Entered App Main \n");
  /* this is a kludge because I can not block until the GID map is up */
  ebbrt::event_manager->Spawn([]() {
    auto id = ebbrt::GenerateStaticEbbId("ThreadRingId");
    auto tr = new ThreadRingMember(id);
    ThreadRingMember::Create(tr,id);
    tring->Init();
    tring->Join();
  });
}
