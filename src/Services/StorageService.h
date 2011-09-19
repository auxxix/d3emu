#ifndef D3EMU_STORAGESERVICE_H
#define D3EMU_STORAGESERVICE_H

#include <stdint.h>

#include "service/storage/storage.pb.h"

#include "Service.h"

#include "../Net/Packet.h"

namespace d3emu
{
	class StorageService : public Service
	{
	public:
		StorageService(uint32_t _service_hash, uint8_t _service_id);
		void Request(const char *packet, int packet_length);
        PacketResponse *Request(PacketRequest &packet);
		std::string Name() const;
        
	private:
		// 0x01
		PacketResponse *ExecuteRequest(PacketRequest &packet);

		// 0x02
		PacketResponse *OpenTableRequest(PacketRequest &packet);

		// 0x03
		PacketResponse *OpenColumnRequest(PacketRequest &packet);
	};
}

#endif
