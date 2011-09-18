#include "Client.h"

namespace d3emu
{
	bool Client::Send(std::string &header, google::protobuf::Message &message)
	{
		int sent = 0;

		std::string built_response;
		built_response.append(header);
		built_response.append(message.SerializeAsString());

		return (sent == built_response.length());
	}

	void Client::set_socket(int socket)
	{
		this->socket_ = socket;
	}

	int Client::socket() const
	{
		return this->socket_;
	}

}