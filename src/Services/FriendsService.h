#ifndef D3EMU_FRIENDSSERVICE
#define D3EMU_FRIENDSSERVICE

#include "service/friends/definition/friends.pb.h"

#include "Service.h"

#include <stdint.h>

// 0xA3DDB1BD bnet.protocol.friends.SubscribeToFriendsRequest
namespace d3emu
{

class FriendsService : public Service
{
public:
	FriendsService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	void SubscribeToFriendsRequest(bnet::protocol::friends::SubscribeToFriendsRequest &request);
};

}

#endif
