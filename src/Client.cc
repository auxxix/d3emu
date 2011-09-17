#include "Client.h"

void d3emu::Client::set_socket(int socket)
{
	this->socket_ = socket;
}

int d3emu::Client::socket() const
{
	return this->socket_;
}
