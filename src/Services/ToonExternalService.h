#ifndef d3emu_ToonExternalService_h
#define d3emu_ToonExternalService_h

#include <stdint.h>

#include "Service.h"

#include "service/toon/toon.pb.h"
#include "service/toon/toon_external.pb.h"

namespace d3emu
{
    class ToonExternalService : public Service
    {
    public:
        ToonExternalService(uint32_t _service_hash, uint8_t _service_id);
        void Request(const char *packet, int packet_length);
        std::string Name() const;
        
    private:
        // 0x01
        void ToonListRequest(bnet::protocol::toon::external::ToonListRequest &request);
        
        // 0x02
        void SelectToonRequest(bnet::protocol::toon::external::SelectToonRequest &request);
        
        // 0x03
        void CreateToonRequest(bnet::protocol::toon::external::CreateToonRequest &request);
    };
}

#endif
