#include <ebbrt/SharedIOBufRef.h>
#include <ebbrt/StaticIOBuf.h>
#include <ebbrt/UniqueIOBuf.h>
#include "IOStreamHandler.h"

void ebbrt::IOStreamHandler::Receive(std::unique_ptr<MutIOBuf> b) { return; }
