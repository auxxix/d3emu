#ifndef D3EMU_FOLLOWERSSERVICE_H
#define D3EMU_FOLLOWERSSERVICE_H

#include "service/followers/definition/followers.pb.h"

#include "Service.h"

#include <stdint.h>

namespace d3emu
{

// 0xE5A11099 bnet.protocol.followers.SubscribeToFollowersRequest

class FollowersService : public Service
{
public:
	FollowersService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	// 0x01
	void SubscribeToFollowersRequest(bnet::protocol::followers::SubscribeToFollowersRequest &request);
};

}

#endif