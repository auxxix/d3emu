#include "Packet.h"

namespace d3emu
{
	void PacketHeader::set_request_id(uint8_t request_id)
	{
		this->request_id_ = request_id;
	}

	void PacketHeader::set_message_size(uint8_t message_size)
	{
		this->message_size_ = message_size;
	}

	void PacketHeader::set_method_id(uint8_t method_id)
	{
		this->method_id_ = method_id;
	}

	void PacketHeader::set_service_id(uint8_t service_id)
	{
		this->service_id_ = service_id;
	}

	uint8_t PacketHeader::service_id() const
	{
		return this->service_id_;
	}

	uint8_t PacketHeader::method_id() const
	{
		return this->method_id_;
	}

	uint8_t PacketHeader::request_id() const
	{
		return this->request_id_;
	}

	uint8_t PacketHeader::message_size() const
	{
		return this->message_size_;
	}

	std::string PacketHeader::SerializeAsString() const
	{
		return std::string(this->raw_bytes_, this->raw_bytes_ + 5);
	}
}