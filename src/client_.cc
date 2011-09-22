#include "Client.h"

namespace d3emu
{
	void Client::set_email(const char *email)
	{
		this->email_ = email;
	}

	void Client::set_email(std::string &email)
	{
		this->email_ = email;
	}

	const std::string &Client::email() const
	{
		return this->email_;
	}

	std::string *Client::mutable_email()
	{
		return &this->email_;
	}
}