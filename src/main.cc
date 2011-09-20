#include <time.h>

#include "Net/Server.h"

int main(int argc, char **argv)
{
	srand((unsigned int)time(0));
    
    boost::asio::io_service io_service;
    d3emu::Server server(io_service, "127.0.0.1", 6543);
    
    if (server.Init())
    {
        boost::system::error_code ec;
        do {
            io_service.run(ec);
        } while (!ec);
    }
    
	return 0;
}
