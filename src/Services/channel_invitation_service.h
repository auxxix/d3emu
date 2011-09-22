#ifndef D3EMU_CHANNELINVITATIONSERVICE_H
#define D3EMU_CHANNELINVITATIONSERVICE_H

#include "Service.h"
#include "service/channel_invitation/definition/channel_invitation.pb.h"

namespace d3emu
{
	namespace services
	{
		class ChannelInvitationService : public Service
		{
		public:
			ChannelInvitationService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x01
			net::PacketResponse *SubscribeRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif