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
			PacketResponse *Request(Client &client, PacketRequest &request_packet);
			std::string Name() const;
        
		private:
			// 0x01
			PacketResponse *ToonListRequest(Client &client, PacketRequest &request_packet);
        
			// 0x02
			PacketResponse *SelectToonRequest(Client &client, PacketRequest &request_packet);
        
			// 0x03
			PacketResponse *CreateToonRequest(Client &client, PacketRequest &request_packet);
		};
	}
}

#endif
