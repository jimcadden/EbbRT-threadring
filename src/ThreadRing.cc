#include <iostream>
#include <ebbrt/IOBuf.h>
#include <ebbrt/UniqueIOBuf.h>
#ifdef __ebbrt__
#include <ebbrt/native/NetUdp.h>
#include <ebbrt/MoveLambda.h>
#else
#include <boost/asio.hpp>
#endif

#include "ThreadRing.h"

ThreadRingMember::ThreadRingMember(ebbrt::EbbId id) : ebbrt::MemberSet<ThreadRingMember>(id) {
	StartListening();
}

void
ThreadRingMember::MemberSetEventSetCreate() {
  std::cout << "MemberSetEventSetCreate Called: " << std::endl;
}

void
ThreadRingMember::MemberSetEventSetDelete() {
  std::cout << "MemberSetEventSetDelete Called: "  << std::endl;
}

void
ThreadRingMember::MemberSetEventMemberAdd(MemberId id) {
  std::cout << "ThreadRing: Added member " << id << std::endl;
	MessageRingMember(id, RingMsgHeader({MessageType::Ping,1969}));
}

void
ThreadRingMember::MemberSetEventMemberDelete(MemberId id) {
  std::cout << "ThreadRing: Removed member " << id << std::endl;
}


void ThreadRingMember::MessageRingMember(MemberId mid, const RingMsgHeader& msg){
  std::cout << "ThreadRing: message member " << mid << std::endl;
  auto buf = ebbrt::MakeUniqueIOBuf(sizeof(RingMsgHeader));
  auto res = reinterpret_cast<RingMsgHeader *>(buf->MutData());
	*res = msg; 
#ifdef __ebbrt__
	auto addr = get_member_address(mid);
	udp_.SendTo(addr, port_, std::move(buf));
#else
  ebbrt::kprintf("ThreadRing message member NOT IMPLEMENTED!!\n");
#endif
}

void ThreadRingMember::StartListening(uint16_t port) {
#ifdef __ebbrt__
  ebbrt::kprintf("ThreadRing starts listening\n");
  udp_.Bind(port);
  udp_.Receive([this](IpAddr addr, uint16_t port, std::unique_ptr<ebbrt::IOBuf> b) {
  auto dp = b->GetDataPointer();
  auto& h = dp.Get<const RingMsgHeader>();
	auto type = static_cast<int>(h.type);
	auto value = h.value;
        std::cout << "ThreadRing received on port " << port
                  << " message size: " << b->Length() << " payload: " << type
                  << ":" << value << std::endl;
		
  });
#else
  ebbrt::kprintf("ThreadRing starts listening NOT IMPLEMENTED!!\n");
#endif
}

ThreadRingMember::IpAddr ThreadRingMember::get_member_address(MemberId mid) {
#ifdef __ebbrt__
  std::array<uint8_t, 4> binary = {0,0,0,0};
  std::cout << "Get members address!" << mid << std::endl;
  auto count = 0;
  auto last = 0;
  auto next = mid.find('.', last);
  while (count < 4 ) {
    auto subs = mid.substr(last, next - last);
    sscanf(subs.c_str(), "%hhu", &binary[count]);
    last = next + 1;
    next = mid.find('.', last);
    count++;
  }
  return ebbrt::Ipv4Address(binary);
#else /* Linux */
  return boost::asio::ip::address_v4::from_string(mid);
#endif
}
