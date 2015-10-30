#include <streambuf>
#include <string>
#include <ebbrt/IOBuf.h>
#include <StreamIOBuf.h>

ebbrt::StreamIOBuf::StreamIOBuf(const IOBuf *p) : p_{ p } {
  assert(p->ComputeChainDataLength() > 0);
  // Iterate past any empty buffers up front
  while (p_->Length() == 0) {
    p_ = p_->Next();
  }
  auto front = reinterpret_cast<char *>(const_cast<uint8_t *>(p_->Data()));
  auto back = reinterpret_cast<char *>(const_cast<uint8_t *>(p_->Tail()));
  setg(front, front, back);
  setp(nullptr, nullptr);
}

std::streamsize ebbrt::StreamIOBuf::showmanyc() { 
  return p_->ComputeChainDataLength() - (gptr()-eback());
}

int ebbrt::StreamIOBuf::underflow() {
  while (epptr() - gptr()) {
    if (!p_->IsChained()) {
      return traits_type::eof();
    }
    p_ = p_->Next();
  auto front = reinterpret_cast<char *>(const_cast<uint8_t *>(p_->Data()));
  auto back = reinterpret_cast<char *>(const_cast<uint8_t *>(p_->Tail()));
    setg(front, front, back);
  }
  auto r = *const_cast<uint8_t *>(p_->Data());
  return r;
}

