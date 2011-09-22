#ifndef D3EMU_CLIENT_H
#define D3EMU_CLIENT_H

#include <google/protobuf/message.h>

namespace d3emu
{
	class Client
	{
	public:
		void set_email(const char *email);
		void set_email(std::string &email);
		const std::string &email() const;
		std::string *mutable_email();

	private:
		std::string email_;
	};
} // d3emu service

#endif