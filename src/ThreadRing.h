#ifndef APPS_THREADRING_SRC_THREADRING_H_
#define APPS_THREADRING_SRC_THREADRING_H_

#include "MemberSet.h"
#include <ebbrt/GlobalStaticIds.h>
#include <ebbrt/SharedEbb.h>

#ifdef __ebbrt__
#include <ebbrt/native/Net.h>
#else
#include <boost/asio.hpp>
#endif

class ThreadRingMember : public ebbrt::SharedEbb<ThreadRingMember>,
                         public ebbrt::MemberSet<ThreadRingMember> {
  using MemberSet::MemberId;
#ifdef __ebbrt__
  using IpAddr =  ebbrt::Ipv4Address;
#else
  using IpAddr =  boost::asio::ip::address_v4;
#endif
 public:
  enum struct MessageType : int {  // event values declared in
    Nil = 0,
    Ping
  };

  struct RingMsgHeader {
    MessageType type;
    int value;
  };

  ThreadRingMember(ebbrt::EbbId id);
  /* GlobalIdMap Event Handlers */
  void MemberSetEventSetCreate();
  void MemberSetEventSetDelete();
  void MemberSetEventMemberAdd(MemberId id) override;
  void MemberSetEventMemberDelete(MemberId id) override;

  void MessageRingMember(MemberId id, const RingMsgHeader& msg);
	void StartListening(uint16_t port = port_);
	private:
	IpAddr get_member_address(MemberId id);
  const static uint16_t port_ = 32123;
#ifdef __ebbrt__
  ebbrt::NetworkManager::UdpPcb udp_;
#endif
};

constexpr auto tring =
    ebbrt::EbbRef<ThreadRingMember>(ebbrt::GenerateStaticEbbId("ThreadRingId"));
#endif  // APPS_THREADRING_SRC_THREADRING_H_
