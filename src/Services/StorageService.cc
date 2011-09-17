#include "StorageService.h"

#include <iostream>

#ifdef _WIN32
	#include <WinSock2.h>
#else
    #include <sys/socket.h>
#endif

#include "../bnet/Account.pb.h"

namespace d3emu
{

StorageService::StorageService(uint32_t _service_hash, uint8_t _service_id)
	: Service(_service_hash, _service_id) 
{
}

void StorageService::ExecuteRequest(bnet::protocol::storage::ExecuteRequest &request)
{
	std::cout << request.GetTypeName() << ":" << std::endl
		<< request.DebugString() << std::endl;

	bnet::protocol::storage::ExecuteResponse response;

	if (!request.query_name().compare("GetGameAccountSettings"))
	{
		for (int i = 0; i < request.operations_size(); i++)
		{
			const bnet::protocol::storage::Operation &request_operation = request.operations(i);
			bnet::protocol::storage::OperationResult *operation = response.add_results();

			operation->mutable_table_id()->set_hash(request_operation.table_id().hash());

			bnet::protocol::storage::Cell *cell = operation->add_data();

			cell->mutable_column_id()->set_hash(request_operation.column_id().hash());
			cell->mutable_row_id()->set_hash(request_operation.row_id().hash());
		}
	}
	else if (!request.query_name().compare("LoadAccountDigest"))
	{
		D3::Account::Digest digest;
		digest.set_version(99);
		digest.set_flags(0);
		digest.mutable_last_played_hero_id()->set_id_high(0);
		digest.mutable_last_played_hero_id()->set_id_low(0);

		D3::Account::BannerConfiguration *banner_configuration = digest.mutable_banner_configuration();
		banner_configuration->set_background_color_index(0);
		banner_configuration->set_banner_index(0);
		banner_configuration->set_pattern(0);
		banner_configuration->set_pattern_color_index(0);
		banner_configuration->set_placement_index(0);
		banner_configuration->set_sigil_main(0);
		banner_configuration->set_sigil_accent(0);
		banner_configuration->set_sigil_color_index(0);
		banner_configuration->set_use_sigil_variant(false);

		for (int i = 0; i < request.operations_size(); i++)
		{
			const bnet::protocol::storage::Operation &request_operation = request.operations(i);
			bnet::protocol::storage::OperationResult *operation = response.add_results();

			operation->mutable_table_id()->set_hash(request_operation.table_id().hash());

			bnet::protocol::storage::Cell *cell = operation->add_data();

			cell->mutable_column_id()->set_hash(request_operation.column_id().hash());
			cell->mutable_row_id()->set_hash(request_operation.row_id().hash());
			cell->set_version(1);
			cell->set_data(digest.SerializeAsString());
		}
	}

	uint8_t header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
	std::string built_response = response.SerializeAsString();
	built_response.insert(built_response.begin(), header, header + 5);

	std::cout << response.GetTypeName() << ":"
		<< std::endl << response.DebugString() << std::endl;
	send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

void StorageService::OpenTableRequest(bnet::protocol::storage::OpenTableRequest &request)
{
	std::cout << request.GetTypeName() << ":" << std::endl
		<< request.DebugString() << std::endl;

	bnet::protocol::storage::OpenTableResponse response;

	uint8_t header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
	std::string built_response = response.SerializeAsString();
	built_response.insert(built_response.begin(), header, header + 5);

	std::cout << response.GetTypeName() << ":"
		<< std::endl << response.DebugString() << std::endl;
	send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

void StorageService::OpenColumnRequest(bnet::protocol::storage::OpenColumnRequest &request)
{
	std::cout << request.GetTypeName() << ":" << std::endl
		<< request.DebugString() << std::endl;

	bnet::protocol::storage::OpenColumnResponse response;

	uint8_t header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
	std::string built_response = response.SerializeAsString();
	built_response.insert(built_response.begin(), header, header + 5);

	std::cout << response.GetTypeName() << ":"
		<< std::endl << response.DebugString() << std::endl;
	send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

void StorageService::Request(const char *packet, int packet_length)
{
	this->set_current_packet(packet, packet_length);

	uint8_t method_id = (uint8_t)packet[1];
	switch (method_id)
	{
		case 0x01:
		{
			bnet::protocol::storage::ExecuteRequest request;
			if (request.ParseFromArray(&packet[6], packet[5]))
				this->ExecuteRequest(request);
			break;
		}

		case 0x02:
		{
			bnet::protocol::storage::OpenTableRequest request;
			if (request.ParseFromArray(&packet[6], packet[5]))
				this->OpenTableRequest(request);
			break;
		}

		case 0x03:
		{
			bnet::protocol::storage::OpenColumnRequest request;
			if (request.ParseFromArray(&packet[6], packet[5]))
				this->OpenColumnRequest(request);
			break;
		}
	}
}

std::string StorageService::Name() const
{
	return std::string("d3emu::StorageService");
}

}