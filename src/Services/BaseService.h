#ifndef D3EMU_BASESERVICE_H
#define D3EMU_BASESERVICE_H

#include "Service.h"

#include "lib/rpc/connection.pb.h"

#include <stdint.h>

namespace d3emu
{
    
class BaseService : public Service
{
public:
    BaseService(uint32_t _service_hash, uint8_t _service_id);
    
    void Request(const char *packet, int packet_length);
    
	std::string Name() const;

private:
    void ConnectRequest(bnet::protocol::connection::ConnectRequest &request);
    void BindRequest(bnet::protocol::connection::BindRequest request);
};

}

#endif
