#ifndef D3EMU_SERVER_H
#define D3EMU_SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

#include "../Services/Service.h"
#include "../Client.h"

namespace d3emu 
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
        void Start();
        void Accept(const boost::system::error_code &error, ServerClient *pending_client);
        boost::asio::io_service &io_service();
        BoundServicesManager &services_manager();
        
    private:
        boost::asio::ip::tcp::endpoint endpoint_;
        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::io_service &io_service_;
        std::vector<ServerClient *> server_clients_;
        BoundServicesManager services_manager_;
    };
}
#endif
