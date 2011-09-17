#ifndef D3EMU_AUTHENTICATIONSERVICE_H
#define D3EMU_AUTHENTICATIONSERVICE_H

#include "Services/Service.h"

#include "service/authentication/authentication.pb.h"

#include <stdint.h>

namespace d3emu
{
class AuthenticationService : public Service
{
public:
	AuthenticationService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	// 0x01
	void LogonRequest(bnet::protocol::authentication::LogonRequest &request);
};
}

#endif