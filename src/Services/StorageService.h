#ifndef D3EMU_STORAGESERVICE_H
#define D3EMU_STORAGESERVICE_H

#include "service/storage/storage.pb.h"

#include "Service.h"

namespace d3emu
{
	namespace Services
	{
		class StorageService : public Service
		{
		public:
			StorageService(uint32_t _service_hash, uint8_t _service_id);
			Net::PacketResponse *Request(Client &client, Net::PacketRequest &packet);
			std::string Name() const;
        
		private:
			// 0x01
			Net::PacketResponse *ExecuteRequest(Client &client, Net::PacketRequest &packet);

			// 0x02
			Net::PacketResponse *OpenTableRequest(Client &client, Net::PacketRequest &packet);

			// 0x03
			Net::PacketResponse *OpenColumnRequest(Client &client, Net::PacketRequest &packet);
		};
	}
}

#endif
