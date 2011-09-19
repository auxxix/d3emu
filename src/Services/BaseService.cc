#include "BaseService.h"
#include "Service.h"

#include <iostream>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif

namespace d3emu 
{

BaseService::BaseService(uint32_t _service_hash, uint8_t _service_id)
: Service(_service_hash, _service_id) 
{
}

PacketResponse *BaseService::Request(Client &client, PacketRequest &request_packet)
{
    PacketResponse *response_packet = 0;
    
    switch (request_packet.header().method_id())
    {
        case 0x01:
        {
            request_packet.set_message(new bnet::protocol::connection::ConnectRequest());
            if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
                response_packet = this->ConnectRequest(client, request_packet);
            else
                request_packet.clear_message();
            break;
        }
            
        case 0x02:
        {
            bnet::protocol::connection::BindRequest request;
            if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
                response_packet = this->BindRequest(client, request_packet);
            else
                request_packet.clear_message();
            break;
        }
    }
    
    return response_packet;
}

void BaseService::ConnectRequest(Client &client, bnet::protocol::connection::ConnectRequest &request)
{
    std::cout << request.GetTypeName() << ":" << std::endl
		<< request.DebugString() << std::endl;
    
    bnet::protocol::connection::ConnectResponse response;
    response.mutable_server_id()->set_label(388207126);
    response.mutable_server_id()->set_epoch((uint32_t)time(0));
    response.mutable_client_id()->set_label(70853);
    response.mutable_client_id()->set_epoch((uint32_t)time(0));
    
    unsigned char header[5] = { 0xfe, 0x00, 0x00, 0x00, response.ByteSize() };
    
    std::string built_response = response.SerializeAsString();
    built_response.insert(built_response.begin(), header, header + 5);
    
	std::cout << "bnet::protocol::connection::ConnectResponse: " << std::endl
		<< response.DebugString() << std::endl;
    send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

void BaseService::BindRequest(Client &client, bnet::protocol::connection::BindRequest request)
{
    std::cout << request.GetTypeName() << ":" << std::endl
		<< request.DebugString() << std::endl;
    
    bnet::protocol::connection::BindResponse response;		
    
    if (this->manager())
	{
		for (int i = 0; i < request.imported_service_hash_size(); i++)
		{
			uint8_t service_id = this->manager()->bound_service_id(request.imported_service_hash(i));
			if (service_id)
			{
				std::cout << "Bound service: " << (int)service_id << ": "
					<< this->manager()->bound_service(service_id)->Name() << std::endl;
				response.add_imported_service_id((google::protobuf::uint32)service_id);
			}
			else
			{
				/* Service hash not supported
				std::cout << "Error: Unknown imported service hash provided: " 
					<< std::hex << std::uppercase << request.imported_service_hash(i) << std::endl;
			
				uint8_t service_id = (uint8_t)(rand() % 254) & 0xFF;
				this->manager()->mutable_bound_services_hashes()->insert(
					BoundServiceHashPair(request.imported_service_hash(i), service_id));
				response.add_imported_service_id(service_id);

				std::cout << "Bound unknown service: " << std::hex << ((unsigned int)service_id & 0xFF) << " : " 
					<< std::hex << request.imported_service_hash(i) << std::endl;
				*/
			}
		}
	}
    
	unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
    std::string built_response = response.SerializeAsString();
    built_response.insert(built_response.begin(), header, header + 5);
    /*
    printf("<-- (Hex): ");
    for (int i = 0; i < built_response.length(); i++)
    {
        printf("%02X ", built_response[i] & 0xff);
    }
    printf("\n");
    */
    std::cout << response.GetTypeName() << ":" << std::endl
		<< response.DebugString() << std::endl;
    send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

std::string BaseService::Name() const
{
	return std::string("d3emu::BaseService");
}

}