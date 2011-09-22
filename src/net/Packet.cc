#include "Packet.h"

#include <iostream>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace d3emu
{
	namespace net
	{
		// PacketHeaderResponse

		PacketHeaderResponse::PacketHeaderResponse()
			: service_id_(0), method_id_(0), request_id_(0), message_size_(0)
		{
		}

		PacketHeaderResponse::PacketHeaderResponse(const char *packet, size_t length)
			: service_id_(0), method_id_(0), request_id_(0), message_size_(0)
		{
			google::protobuf::io::CodedInputStream *input_stream =
				new google::protobuf::io::CodedInputStream((const uint8_t *)packet, (int)length);
        
			input_stream->ReadRaw(&this->service_id_, 1);
			input_stream->ReadVarint32(&this->method_id_);
			input_stream->ReadRaw(&this->request_id_, 2);
			input_stream->ReadVarint32(&this->message_size_);
        
			delete input_stream;
		}

		PacketHeaderResponse::PacketHeaderResponse(const uint8_t *packet, size_t length)
			: service_id_(0), method_id_(0), request_id_(0), message_size_(0)
		{
			google::protobuf::io::CodedInputStream *input_stream =
				new google::protobuf::io::CodedInputStream(packet, (int)length);
        
			input_stream->ReadRaw(&this->service_id_, 1);
			input_stream->ReadVarint32(&this->method_id_);
			input_stream->ReadRaw(&this->request_id_, 2);
			input_stream->ReadVarint32(&this->message_size_);
        
			delete input_stream;
		}

		PacketHeaderResponse::PacketHeaderResponse(std::string &packet)
			: service_id_(0), method_id_(0), request_id_(0), message_size_(0)
		{
			google::protobuf::io::CodedInputStream *input_stream =
				new google::protobuf::io::CodedInputStream((const uint8_t *)packet.c_str(), (int)packet.length());
        
			input_stream->ReadRaw(&this->service_id_, 1);
			input_stream->ReadVarint32(&this->method_id_);
			input_stream->ReadRaw(&this->request_id_, 2);
			input_stream->ReadVarint32(&this->message_size_);
        
			delete input_stream;
		}

		void PacketHeaderResponse::set_request_id(uint16_t request_id)
		{
			this->request_id_ = request_id;
		}

		void PacketHeaderResponse::set_message_size(uint32_t message_size)
		{
			this->message_size_ = message_size;
		}

		void PacketHeaderResponse::set_method_id(uint32_t method_id)
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

		uint32_t PacketHeaderResponse::method_id() const
		{
			return this->method_id_;
		}

		uint16_t PacketHeaderResponse::request_id() const
		{
			return this->request_id_;
		}

		uint32_t PacketHeaderResponse::message_size() const
		{
			return this->message_size_;
		}

		std::string PacketHeaderResponse::SerializeAsString() const
		{
			std::string str;
        
			google::protobuf::io::ZeroCopyOutputStream *raw_output =
				new google::protobuf::io::StringOutputStream(&str);
			google::protobuf::io::CodedOutputStream *output_stream =
				new google::protobuf::io::CodedOutputStream(raw_output);
        
			output_stream->WriteRaw(&this->service_id_, 1);
			output_stream->WriteVarint32(this->method_id_);
			output_stream->WriteRaw((uint8_t *)&this->request_id_, 2);
			output_stream->WriteVarint32(this->message_size_);
        
			delete output_stream;
			delete raw_output;
        
			return str;
		}
    
		bool PacketHeaderResponse::AppendToString(std::string *str) const
		{
			str->append(this->SerializeAsString());
			return true;
		}

		// PacketHeaderRequest

		PacketHeaderRequest::PacketHeaderRequest()
			: service_id_(0), method_id_(0), request_id_(0), unknown_(0), message_size_(0)
		{
		}

		PacketHeaderRequest::PacketHeaderRequest(const char *packet, size_t length)
			: service_id_(0), method_id_(0), request_id_(0), unknown_(0), message_size_(0)
		{
			google::protobuf::io::CodedInputStream *input_stream =
				new google::protobuf::io::CodedInputStream((const uint8_t *)packet, (int)length);
        
			input_stream->ReadRaw(&this->service_id_, 1);
			input_stream->ReadVarint32(&this->method_id_);
			input_stream->ReadRaw(&this->request_id_, 2);
			input_stream->ReadVarint64(&this->unknown_);
			input_stream->ReadVarint32(&this->message_size_);
        
			delete input_stream;
		}

		PacketHeaderRequest::PacketHeaderRequest(const uint8_t *packet, size_t length)
			: service_id_(0), method_id_(0), request_id_(0), unknown_(0), message_size_(0)
		{
			google::protobuf::io::CodedInputStream *input_stream =
				new google::protobuf::io::CodedInputStream(packet, (int)length);
        
			input_stream->ReadRaw(&this->service_id_, 1);
			input_stream->ReadVarint32(&this->method_id_);
			input_stream->ReadRaw(&this->request_id_, 2);
			input_stream->ReadVarint64(&this->unknown_);
			input_stream->ReadVarint32(&this->message_size_);
        
			delete input_stream;
		}

		PacketHeaderRequest::PacketHeaderRequest(std::string &packet)
			: service_id_(0), method_id_(0), request_id_(0), unknown_(0), message_size_(0)
		{
			google::protobuf::io::CodedInputStream *input_stream =
				new google::protobuf::io::CodedInputStream((const uint8_t *)packet.c_str(), (int)packet.length());
        
			input_stream->ReadRaw(&this->service_id_, 1);
			input_stream->ReadVarint32(&this->method_id_);
			input_stream->ReadRaw(&this->request_id_, 2);
			input_stream->ReadVarint64(&this->unknown_);
			input_stream->ReadVarint32(&this->message_size_);
        
			delete input_stream;
		}

		void PacketHeaderRequest::set_request_id(uint16_t request_id)
		{
			this->request_id_ = request_id;
		}
    
		void PacketHeaderRequest::set_unknown(uint64_t unknown)
		{
			this->unknown_ = unknown;
		}

		void PacketHeaderRequest::set_message_size(uint32_t message_size)
		{
			this->message_size_ = message_size;
		}

		void PacketHeaderRequest::set_method_id(uint32_t method_id)
		{
			this->method_id_ = method_id;
		}

		void PacketHeaderRequest::set_service_id(uint8_t service_id)
		{
			this->service_id_ = service_id;
		}

		uint8_t PacketHeaderRequest::service_id() const
		{
			return this->service_id_;
		}

		uint32_t PacketHeaderRequest::method_id() const
		{
			return this->method_id_;
		}

		uint16_t PacketHeaderRequest::request_id() const
		{
			return this->request_id_;
		}
    
		uint64_t PacketHeaderRequest::unknown() const
		{
			return this->unknown_;
		}

		uint32_t PacketHeaderRequest::message_size() const
		{
			return this->message_size_;
		}

		std::string PacketHeaderRequest::SerializeAsString() const
		{
			std::string str;
        
			google::protobuf::io::ZeroCopyOutputStream *raw_output =
				new google::protobuf::io::StringOutputStream(&str);
			google::protobuf::io::CodedOutputStream *output_stream =
				new google::protobuf::io::CodedOutputStream(raw_output);
        
			output_stream->WriteRaw(&this->service_id_, 1);
			output_stream->WriteVarint32(this->method_id_);
			output_stream->WriteRaw((uint8_t *)&this->request_id_, 2);
			output_stream->WriteVarint64(this->unknown_);
			output_stream->WriteVarint32(this->message_size_);
        
			delete output_stream;
			delete raw_output;
        
			return str;
		}
    
		bool PacketHeaderRequest::AppendToString(std::string *str) const
		{
			str->append(this->SerializeAsString());
			return true;
		}

		// PacketRequest

		PacketRequest::PacketRequest()
		{
			this->clear_has_message();
		}

		PacketRequest::PacketRequest(const char *packet, size_t length)
			: header_(packet, 6), message_data_((char *)&packet[6], (char *)&packet[6] + packet[5])
		{
		}

		PacketRequest::PacketRequest(const uint8_t *packet, size_t length)
			: header_(packet, 6), message_data_((char *)&packet[6], (char *)&packet[6] + packet[5])
		{
		}

		PacketRequest::PacketRequest(std::string &packet)
			: header_(packet), message_data_(packet.begin() + 6, packet.begin() + 6 + packet[5])
		{
		}
    
		PacketRequest::~PacketRequest()
		{
			if (this->has_message())
				this->clear_message();
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
				this->header_.set_message_size(this->message_->ByteSize());
			}
			else
			{
				this->clear_message();
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
    
		std::string PacketRequest::SerializeAsString() const
		{
			std::string request;
			request.append(this->header().SerializeAsString());
			if (this->has_message())
				this->message()->AppendToString(&request);
			return request;
		}
    
		bool PacketRequest::AppendToString(std::string *str) const
		{
			str->append(this->SerializeAsString());
			return true;
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
    
		PacketResponse::~PacketResponse()
		{
			if (this->has_message())
				this->clear_message();
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
				this->header_.set_message_size(this->message_->ByteSize());
			}
			else
			{
				this->clear_message();
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
    
		std::string PacketResponse::SerializeAsString() const
		{
			std::string response;
			response.append(this->header().SerializeAsString());
			if (this->has_message())
				this->message()->AppendToString(&response);
			return response;
		}
    
		bool PacketResponse::AppendToString(std::string *str) const
		{
			str->append(this->SerializeAsString());
			return true;
		}
	}
}