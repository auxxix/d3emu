#ifndef d3emu_ToonExternalService_h
#define d3emu_ToonExternalService_h

#include "Service.h"
#include "service/toon/toon.pb.h"
#include "service/toon/toon_external.pb.h"

namespace d3emu
{
	namespace Services
	{
		class ToonExternalService : public Service
		{
		public:
			ToonExternalService(uint32_t _service_hash, uint8_t _service_id);
			Net::PacketResponse *Request(Client &client, Net::PacketRequest &request_packet);
			std::string Name() const;
        
		private:
			// 0x01
			Net::PacketResponse *ToonListRequest(Client &client, Net::PacketRequest &request_packet);
        
			// 0x02
			Net::PacketResponse *SelectToonRequest(Client &client, Net::PacketRequest &request_packet);
        
			// 0x03
			Net::PacketResponse *CreateToonRequest(Client &client, Net::PacketRequest &request_packet);
		};
	}
}

#endif
