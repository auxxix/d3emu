#ifndef d3emu_ToonExternalService_h
#define d3emu_ToonExternalService_h

#include "Service.h"
#include "service/toon/toon.pb.h"
#include "service/toon/toon_external.pb.h"

namespace d3emu
{
	namespace services
	{
		class ToonExternalService : public Service
		{
		public:
			ToonExternalService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;
        
		private:
			// 0x01
			net::PacketResponse *ToonListRequest(Client &client, net::PacketRequest &request_packet);
        
			// 0x02
			net::PacketResponse *SelectToonRequest(Client &client, net::PacketRequest &request_packet);
        
			// 0x03
			net::PacketResponse *CreateToonRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif
