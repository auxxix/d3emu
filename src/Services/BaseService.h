#ifndef D3EMU_BASESERVICE_H
#define D3EMU_BASESERVICE_H

#include "Service.h"
#include "lib/rpc/connection.pb.h"

namespace d3emu
{
	namespace Services
	{
		class BaseService : public Service
		{
		public:
			BaseService(uint32_t _service_hash, uint8_t _service_id);
        
			Net::PacketResponse *Request(Client &client, Net::PacketRequest &request_packet);
        
			std::string Name() const;

		private:
			Net::PacketResponse *ConnectRequest(Client &client, Net::PacketRequest &request_packet);
			Net::PacketResponse *BindRequest(Client &client, Net::PacketRequest &request_packet);
		};
	}
}

#endif
