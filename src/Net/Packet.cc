#include "Packet.h"

#include <iostream>

namespace d3emu
{
	// PacketHeaderResponse

	PacketHeaderResponse::PacketHeaderResponse()
	{
	}

	PacketHeaderResponse::PacketHeaderResponse(const char *packet, size_t length)
	{
		PacketHeaderResponse((uint8_t *)packet, length);
	}

	PacketHeaderResponse::PacketHeaderResponse(const uint8_t *packet, size_t length)
	{
		PacketHeaderResponse();

		if (length >= 5)
		{
			this->set_service_id(packet[0]);
			this->set_method_id(packet[1]);
			this->set_request_id(packet[2]);
			this->set_message_size(packet[4]);
		}
	}

	PacketHeaderResponse::PacketHeaderResponse(std::string &packet)
	{
		PacketHeaderResponse();

		if (packet.length() >= 5)
		{
			this->set_service_id(packet[0]);
			this->set_method_id(packet[1]);
			this->set_request_id(packet[2]);
			this->set_message_size(packet[4]);
		}
	}

	void PacketHeaderResponse::set_request_id(uint8_t request_id)
	{
		this->request_id_ = request_id;
	}

	void PacketHeaderResponse::set_message_size(uint8_t message_size)
	{
		this->message_size_ = message_size;
	}

	void PacketHeaderResponse::set_method_id(uint8_t method_id)
	{
		this->method_id_ = method_id;
	}

	void PacketHeaderResponse::set_service_id(uint8_t service_id)
	{
		this->service_id_ = service_id;
	}

	uint8_t PacketHeaderResponse::service_id() const
	{
		return this->service_id_;
	}

	uint8_t PacketHeaderResponse::method_id() const
	{
		return this->method_id_;
	}

	uint8_t PacketHeaderResponse::request_id() const
	{
		return this->request_id_;
	}

	uint8_t PacketHeaderResponse::message_size() const
	{
		return this->message_size_;
	}

	std::string PacketHeaderResponse::SerializeAsString() const
	{
		char bytes[5] = { this->service_id(), this->method_id(), 
			this->request_id(), 0x00, this->message_size() };
		return std::string(bytes, bytes + 5);
	}

	// PacketHeaderRequest

	PacketHeaderRequest::PacketHeaderRequest()
	{
        this->set_service_id(0);
        this->set_method_id(0);
        this->set_request_id(0);
        this->set_message_size(0);
	}

	PacketHeaderRequest::PacketHeaderRequest(const char *packet, size_t length)
        : service_id_(packet[0]), method_id_(packet[1]), request_id_(packet[2]), message_size_(packet[5])
	{
	}

	PacketHeaderRequest::PacketHeaderRequest(const uint8_t *packet, size_t length)
        : service_id_(packet[0]), method_id_(packet[1]), request_id_(packet[2]), message_size_(packet[5])
	{
	}

	PacketHeaderRequest::PacketHeaderRequest(std::string &packet)
        : service_id_(packet[0]), method_id_(packet[1]), request_id_(packet[2]), message_size_(packet[5])
	{
	}

	void PacketHeaderRequest::set_request_id(unsigned int request_id)
	{
		this->request_id_ = request_id;
	}

	void PacketHeaderRequest::set_message_size(unsigned int message_size)
	{
		this->message_size_ = message_size;
	}

	void PacketHeaderRequest::set_method_id(unsigned int _method_id)
	{
		this->method_id_ = _method_id;
	}

	void PacketHeaderRequest::set_service_id(unsigned int service_id)
	{
		this->service_id_ = service_id;
	}

	unsigned int PacketHeaderRequest::service_id() const
	{
		return this->service_id_;
	}

	unsigned int PacketHeaderRequest::method_id() const
	{
        return this->method_id_;
	}

	unsigned int PacketHeaderRequest::request_id() const
	{
		return this->request_id_;
	}

	unsigned int PacketHeaderRequest::message_size() const
	{
		return this->message_size_;
	}

	std::string PacketHeaderRequest::SerializeAsString() const
	{
		char bytes[6] = { this->service_id(), this->method_id_, 
			this->request_id(), 0x00, 0x00, this->message_size() };
		return std::string(bytes, bytes + 6);
	}

	// PacketRequest

	PacketRequest::PacketRequest()
	{
		this->clear_has_message();
	}

	PacketRequest::PacketRequest(const char *packet, size_t length)
	{
		PacketRequest((uint8_t *)packet, length);
	}

	PacketRequest::PacketRequest(const uint8_t *packet, size_t length)
		: header_(packet, 6), message_data_((char *)&packet[6], (char *)&packet[6] + packet[5])
	{
		PacketRequest();
	}

	PacketRequest::PacketRequest(std::string &packet)
		: header_(packet), message_data_(packet.begin() + 6, packet.begin() + 6 + packet[5])
	{
		PacketRequest();
	}

	const PacketHeaderRequest &PacketRequest::header() const
	{
		return this->header_;
	}

	PacketHeaderRequest *PacketRequest::mutable_header()
	{
		return &this->header_;
	}

    void PacketRequest::clear_message()
    {
        if (this->message_)
        {
            delete this->message_;
            this->message_ = 0;
        }
        
        this->clear_has_message();
    }
    
	void PacketRequest::set_message(google::protobuf::Message *message)
	{
		if (message)
		{
			this->set_has_message();
			this->message_ = message;
		}
	}

	bool PacketRequest::has_message() const
	{
		return this->has_message_;
	}
	
    google::protobuf::Message *PacketRequest::message() const
    {
        return this->message_;
    }
    
	google::protobuf::Message *PacketRequest::mutable_message()
	{
		return this->message_;
	}

	std::string PacketRequest::message_data() const
	{
		return this->message_data_;
	}

	void PacketRequest::clear_has_message()
	{
		this->message_ = 0;
		this->has_message_ = false;
	}

	void PacketRequest::set_has_message()
	{
		this->has_message_ = true;
	}
}