#ifndef D3EMU_PACKET_H
#define D3EMU_PACKET_H

#include <google/protobuf/message.h>
#include <stdint.h>

namespace d3emu
{
	class PacketHeaderRequest
	{
	public:
		PacketHeaderRequest();
		PacketHeaderRequest(const char *packet, size_t length);
		PacketHeaderRequest(const uint8_t *packet, size_t length);
		PacketHeaderRequest(std::string &packet);

		void set_service_id(uint8_t service_id);
		void set_method_id(uint8_t method_id);
		void set_request_id(uint8_t request_id);
		void set_message_size(uint8_t message_size);

		uint8_t service_id() const;
		uint8_t method_id() const;
		uint8_t request_id() const;
		uint8_t message_size() const;

		std::string SerializeAsString() const;

	private:
		uint8_t service_id_;
		uint8_t method_id_;
		uint8_t request_id_;
		uint8_t message_size_;
	};
	
	class PacketHeaderResponse
	{
	public:
		PacketHeaderResponse();
		PacketHeaderResponse(const char *packet, size_t length);
		PacketHeaderResponse(const uint8_t *packet, size_t length);
		PacketHeaderResponse(std::string &packet);

		void set_service_id(uint8_t service_id);
		void set_method_id(uint8_t method_id);
		void set_request_id(uint8_t request_id);
		void set_message_size(uint8_t message_size);

		uint8_t service_id() const;
		uint8_t method_id() const;
		uint8_t request_id() const;
		uint8_t message_size() const;

		std::string SerializeAsString() const;

	private:
		uint8_t service_id_;
		uint8_t method_id_;
		uint8_t request_id_;
		uint8_t message_size_;
	};

	class PacketRequest
	{
	public:
		PacketRequest();
		PacketRequest(const char *packet, size_t length);
		PacketRequest(const uint8_t *packet, size_t length);
		PacketRequest(std::string &packet);

		const PacketHeaderRequest &header() const;
		PacketHeaderRequest *mutable_header();

		void set_message(google::protobuf::Message *message);
		bool has_message() const;
		google::protobuf::Message *mutable_message();

		std::string message_data() const;

	private:
		void clear_has_message();
		void set_has_message();

		std::string message_data_;
		PacketHeaderRequest header_;
		google::protobuf::Message *message_;
		bool has_message_;
	};

	class PacketResponse
	{

	};

	class Packet
	{
	public:
		void set_message(google::protobuf::Message *_message);
		google::protobuf::Message *message();

	private:
		std::string header_;
		google::protobuf::Message *message_;
	};

	
}

#endif