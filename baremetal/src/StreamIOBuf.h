//          Copyright Boston University SESA Group 2013 - 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#ifndef EBBRT_IOBUFSTREAM_H_
#define EBBRT_IOBUFSTREAM_H_

#include <streambuf>
#include <string>
#include <ebbrt/IOBuf.h>

namespace ebbrt {
class StreamIOBuf : public std::streambuf {
public:
  StreamIOBuf(const IOBuf *p);
  virtual ~StreamIOBuf() {}

protected:
  std::streamsize showmanyc();
  int underflow();
  // put functions
  int_type overflow(int_type c) { return traits_type::eof(); }
  std::streamsize xsputn(const char_type *s, std::streamsize count) {
    return 0;
  };
  int_type pbackfail(int_type c) { return traits_type::eof(); }

private:
  const IOBuf *p_{ nullptr };
  size_t offset_{ 0 };
};
}

#endif // EBBRT_IOBUFSTREAM_H_
