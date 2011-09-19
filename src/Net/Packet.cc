#include "Packet.h"

#include <iostream>

namespace d3emu
{
	// PacketHeaderResponse

	PacketHeaderResponse::PacketHeaderResponse()
        : service_id_(0), method_id_(0), request_id_(0), message_size_(0)
	{
	}

	PacketHeaderResponse::PacketHeaderResponse(const char *packet, size_t length)
        : service_id_(packet[0]), method_id_(packet[1]), request_id_(packet[2]), message_size_(packet[4])
	{
	}

	PacketHeaderResponse::PacketHeaderResponse(const uint8_t *packet, size_t length)
        : service_id_(packet[0]), method_id_(packet[1]), request_id_(packet[2]), message_size_(packet[4])
	{
	}

	PacketHeaderResponse::PacketHeaderResponse(std::string &packet)
        : service_id_(packet[0]), method_id_(packet[1]), request_id_(packet[2]), message_size_(packet[4])
	{
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
		char bytes[5] = { this->service_id_, this->method_id_, 
			this->request_id_, 0x00, this->message_size_ };
		return std::string(bytes, bytes + 5);
	}

	// PacketHeaderRequest

	PacketHeaderRequest::PacketHeaderRequest()
        : service_id_(0), method_id_(0), request_id_(0), message_size_(0)
    {
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

	void PacketHeaderRequest::set_request_id(uint8_t request_id)
	{
		this->request_id_ = request_id;
	}

	void PacketHeaderRequest::set_message_size(uint8_t message_size)
	{
		this->message_size_ = message_size;
	}

	void PacketHeaderRequest::set_method_id(uint8_t _method_id)
	{
		this->method_id_ = _method_id;
	}

	void PacketHeaderRequest::set_service_id(uint8_t service_id)
	{
		this->service_id_ = service_id;
	}

	uint8_t PacketHeaderRequest::service_id() const
	{
		return this->service_id_;
	}

	uint8_t PacketHeaderRequest::method_id() const
	{
        return this->method_id_;
	}

	uint8_t PacketHeaderRequest::request_id() const
	{
		return this->request_id_;
	}

	uint8_t PacketHeaderRequest::message_size() const
	{
		return this->message_size_;
	}

	std::string PacketHeaderRequest::SerializeAsString() const
	{
		char bytes[6] = { this->service_id_, this->method_id_, 
			this->request_id_, 0x00, 0x00, this->message_size_ };
		return std::string(bytes, bytes + 6);
	}

	// PacketRequest

	PacketRequest::PacketRequest()
	{
		this->clear_has_message();
	}

	PacketRequest::PacketRequest(const char *packet, size_t length)
	{
		this->clear_has_message();
	}

	PacketRequest::PacketRequest(const uint8_t *packet, size_t length)
		: header_(packet, 6), message_data_((char *)&packet[6], (char *)&packet[6] + packet[5])
	{
		this->clear_has_message();
	}

	PacketRequest::PacketRequest(std::string &packet)
		: header_(packet), message_data_(packet.begin() + 6, packet.begin() + 6 + packet[5])
	{
		this->clear_has_message();
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
    
    // PacketResponse
    
    PacketResponse::PacketResponse()
	{
        this->clear_has_message();
	}
    
	PacketResponse::PacketResponse(const char *packet, size_t length)
        : header_(packet, 5), message_data_((char *)&packet[5], (char *)&packet[5] + packet[4])
	{
        this->clear_has_message();
	}
    
	PacketResponse::PacketResponse(const uint8_t *packet, size_t length)
        : header_(packet, 5), message_data_((char *)&packet[5], (char *)&packet[5] + packet[4])
	{
		this->clear_has_message();
	}
    
	PacketResponse::PacketResponse(std::string &packet)
        : header_(packet), message_data_(packet.begin() + 5, packet.begin() + 5 + packet[4])
	{
		this->clear_has_message();
	}
    
	const PacketHeaderResponse &PacketResponse::header() const
	{
		return this->header_;
	}
    
	PacketHeaderResponse *PacketResponse::mutable_header()
	{
		return &this->header_;
	}
    
    void PacketResponse::clear_message()
    {
        if (this->message_)
        {
            delete this->message_;
            this->message_ = 0;
        }
        
        this->clear_has_message();
    }
    
	void PacketResponse::set_message(google::protobuf::Message *message)
	{
		if (message)
		{
			this->set_has_message();
			this->message_ = message;
		}
	}
    
	bool PacketResponse::has_message() const
	{
		return this->has_message_;
	}
	
    google::protobuf::Message *PacketResponse::message() const
    {
        return this->message_;
    }
    
	google::protobuf::Message *PacketResponse::mutable_message()
	{
		return this->message_;
	}
    
	std::string PacketResponse::message_data() const
	{
		return this->message_data_;
	}
    
	void PacketResponse::clear_has_message()
	{
		this->message_ = 0;
		this->has_message_ = false;
	}
    
	void PacketResponse::set_has_message()
	{
		this->has_message_ = true;
	}
}