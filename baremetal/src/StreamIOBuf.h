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
  virtual ~StreamIOBuf() {}

protected:
  StreamIOBuf() 
  StreamIOBuf(const StreamIOBuf &rhs) {}
  explicit StreamIOBuf(const IOBuf *p) : p_{ p } {}
  // operator=
  // swap
  //LOCAL
  // imbue 
  //POSITIONING
  // StreamIOBuf* setbuf( char_type* s, std::streamsize n )
  // seakoff
  // seakpos
  // sync
  // GET AREA
  std::streamsize showmanyc(){ return -1; }
  int_type underflow(){ return std::char_traits<char>::eof(); }
  //int_type uflow() // The base class version calls underflow() increments gptr().
  std::streamsize xsgetn( char_type* s, std::streamsize count ) { return 0; }
  char_type* eback() { return nullptr; };
  char_type* gprt() { return nullptr; };
  char_type* egprt() { return nullptr; };
  void gpump( int count ) {};
  void setg( char_type* gbeg, char_type* gcurr, char_type* gend );
  // PUT AREA
  // int_type overflow(int_type c){ return Traits:eof(); }
  // std::streamsize xsputn( const char_type* s, std::streamsize count );
  // char_type* pbase() { return nullptr; }  const;
  // char_type* pptr() { return nullptr; }  const;
  // char_type* epptr() { return nullptr; }  const;
  // void pbump( int count ) {}
  // void setp( char_type* pbeg, char_type* pend ) {}
  // int_type pbackfail(int_type c){ return Traits:eof(); }
private:
  const IOBuf *p_{ nullptr };
  size_t offset_{ 0 };
};
}

#endif // EBBRT_IOBUFSTREAM_H_
