#ifndef D3EMU_STORAGESERVICE_H
#define D3EMU_STORAGESERVICE_H

#include <stdint.h>

#include "service/storage/storage.pb.h"

#include "Service.h"

namespace d3emu
{

class StorageService : public Service
{
public:
	StorageService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	// 0x01
	void ExecuteRequest(bnet::protocol::storage::ExecuteRequest &request);

	// 0x02
	void OpenTableRequest(bnet::protocol::storage::OpenTableRequest &request);

	// 0x03
	void OpenColumnRequest(bnet::protocol::storage::OpenColumnRequest &request);
};

}

#endif
