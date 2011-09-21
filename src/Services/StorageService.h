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
			PacketResponse *Request(Client &client, PacketRequest &packet);
			std::string Name() const;
        
		private:
			// 0x01
			PacketResponse *ExecuteRequest(Client &client, PacketRequest &packet);

			// 0x02
			PacketResponse *OpenTableRequest(Client &client, PacketRequest &packet);

			// 0x03
			PacketResponse *OpenColumnRequest(Client &client, PacketRequest &packet);
		};
	}
}

#endif
