#ifndef D3EMU_CHANNELINVITATIONSERVICE_H
#define D3EMU_CHANNELINVITATIONSERVICE_H

#include <stdint.h>

#include "Service.h"

#include "service/channel_invitation/definition/channel_invitation.pb.h"

namespace d3emu
{

class ChannelInvitationService : public Service
{
public:
	ChannelInvitationService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	// 0x01
	void SubscribeRequest(bnet::protocol::channel_invitation::SubscribeRequest &request);
};

}

#endif