#ifndef D3EMU_CLIENT_H
#define D3EMU_CLIENT_H

namespace d3emu {

class Client
{
public:
	void set_socket(int socket);
	int socket() const;

private:
	int socket_;
};

} // d3emu service

#endif