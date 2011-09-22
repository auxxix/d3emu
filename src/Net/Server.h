#ifndef D3EMU_SERVER_H
#define D3EMU_SERVER_H

// Minimum of Windows XP for boost.
#if defined(_WIN32) && !defined(_WIN_32_WINNT) 
# define _WIN32_WINNT 0x502
#endif

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "../services/service.h"
#include "../Client.h"

#include <set>

namespace d3emu 
{
	namespace net
	{
		class Server;
    
		class ServerClient
		{
		public:
			ServerClient(boost::asio::io_service &io_service, Server &server);
			void Start();
			void Receive(const boost::system::error_code& error, std::size_t bytes_transferred);
			boost::asio::io_service &io_service();
			boost::asio::ip::tcp::socket &socket();
			Server &server();
        
		private:
			boost::asio::io_service &io_service_;
			boost::asio::ip::tcp::socket socket_;
			Server &server_;
			char buffer_[2048];
			Client client_;
		};

		class Server
		{
		public:
			Server(boost::asio::io_service &io_service, const char *host, short port);
			bool Init();
			void Accept(const boost::system::error_code &error, ServerClient *pending_client);
			boost::asio::io_service &io_service();
			std::set<ServerClient *> &server_clients();
			services::BoundServicesManager &services_manager();
			void RemoveServerClient(ServerClient *server_client);
        
		private:
			boost::asio::ip::tcp::endpoint endpoint_;
			boost::asio::ip::tcp::acceptor acceptor_;
			boost::asio::io_service &io_service_;
			std::set<ServerClient *> server_clients_;
			services::BoundServicesManager services_manager_;
		};
	}
}
#endif
