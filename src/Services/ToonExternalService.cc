#include "ToonExternalService.h"

#include <iostream>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
#endif

namespace d3emu
{
    // 0x4124C31B bnet.protocol.toon.external.*
    
    ToonExternalService::ToonExternalService(uint32_t _service_hash, uint8_t _service_id)
        : Service(_service_hash, _service_id) 
    {
    }
    
    void ToonExternalService::ToonListRequest(bnet::protocol::toon::external::ToonListRequest &request)
    {
        std::cout << request.GetTypeName() << ":" << std::endl << request.DebugString() << std::endl;
        
        bnet::protocol::toon::external::ToonListResponse response;
        
        unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
        std::string built_response = response.SerializeAsString();
        built_response.insert(built_response.begin(), header, header + 5);
        
        std::cout << response.GetTypeName() << ":" << std::endl << response.DebugString() << std::endl;
        send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
    }
    
    void ToonExternalService::CreateToonRequest(bnet::protocol::toon::external::CreateToonRequest &request)
    {
        std::cout << request.GetTypeName() << ":" << std::endl << request.DebugString() << std::endl;
        
        bnet::protocol::toon::external::CreateToonResponse response;
        
        /*
        for (int i = 0; i < request.attribute_size(); i++)
        {
            // http://pastebin.com/ULfdcMba
            D3::OnlineService::HeroCreateParams params;
            params.ParseFromString(request.attribute(i).value().message_value());
            
            std::cout << params.GetTypeName() << ":" << std::endl
                << params.DebugString() << std::endl;
        }
         */
        
        response.mutable_toon()->set_low(2L);
        response.mutable_toon()->set_high(0x300016200004433L);
        
        unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
        std::string built_response = response.SerializeAsString();
        built_response.insert(built_response.begin(), header, header + 5);
        
		for (int i = 0; i < (int)built_response.size(); ++i)
		{
			std::cout << std::hex << std::uppercase << ((uint8_t)built_response[i] & 0xff)
            << " ";
		}
        
		std::cout << std::endl;
        
        std::cout << response.GetTypeName() << ":" << std::endl << response.DebugString() << std::endl;
        send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
    }
    
    void ToonExternalService::Request(const char *packet, int packet_length)
    {
        this->set_current_packet(packet, packet_length);
        
        switch ((uint8_t)packet[1])
        {
            case 0x01:
            {
                bnet::protocol::toon::external::ToonListRequest request;
                if (request.ParseFromArray(&packet[6], packet[5]))
                    this->ToonListRequest(request);
                break;
            }
                
            case 0x03:
            {
                bnet::protocol::toon::external::CreateToonRequest request;
                if (request.ParseFromArray(&packet[6], packet[5]))
                    this->CreateToonRequest(request);
                break;
            }
        }
    }
    
    std::string ToonExternalService::Name() const
    {
        return std::string("d3emu::ToonListService");
    }
    
}