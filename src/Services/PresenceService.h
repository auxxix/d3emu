#ifndef D3EMU_PRESENCESERVICE_H
#define D3EMU_PRESENCESERVICE_H

#include <stdint.h>

#include "service/presence/presence.pb.h"

#include "Service.h"

namespace d3emu
{
// 0xFA0796FF bnet.protocol.presence.SubscribeRequest

class PresenceService : public Service
{
public:
	PresenceService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	void SubscribeRequest(bnet::protocol::presence::SubscribeRequest &request);
};

}

#endif
