#ifndef D3EMU_CLIENT_H
#define D3EMU_CLIENT_H

#include <google/protobuf/message.h>

namespace d3emu
{
	class Client
	{
	public:
		virtual bool Send(std::string &header, google::protobuf::Message &message);
		void set_socket(int socket);
		int socket() const;

	private:
		int socket_;
	};
} // d3emu service

#endif