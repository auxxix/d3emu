#ifndef D3EMU_USERMANAGERSERVICE_H
#define D3EMU_USERMANAGERSERVICE_H

#include <stdint.h>

#include "Service.h"

#include "service/user_manager/user_manager.pb.h"

namespace d3emu
{

class UserManagerService : public Service
{
public:
	UserManagerService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	void SubscribeToUserManagerRequest(bnet::protocol::user_manager::SubscribeToUserManagerRequest &request);
};

}

#endif