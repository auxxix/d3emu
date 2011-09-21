#include "Server.h"

namespace d3emu
{
	namespace Net
	{
		ServerClient::ServerClient(boost::asio::io_service &io_service, Server &server)
			: io_service_(io_service), socket_(io_service), server_(server)
		{
		}
    
		void ServerClient::Start()
		{
			this->socket_.async_receive(boost::asio::buffer(this->buffer_, 2048),
				boost::bind(&ServerClient::Receive, this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
        
		}
    
		void ServerClient::Receive(const boost::system::error_code& error, std::size_t bytes_transferred)
		{
			if (!error)
			{
				Services::Service *service = this->server_.services_manager().bound_service(this->buffer_[0]);
            
				if (!service)
				{
					std::cout << "Couldn't find service handler for service id '" 
						<< std::hex << ((unsigned int)this->buffer_[0] & 0xff) << "'" << std::endl;
				}
				else
				{
					Client client;
					Net::PacketRequest request_packet(this->buffer_, bytes_transferred);
					Net::PacketResponse *response_packet = service->Request(client, request_packet);
                
					if (response_packet)
					{
						std::cout << response_packet->message()->GetTypeName() << std::endl
							<< response_packet->message()->DebugString() << std::endl;
                    
						std::string built_response = response_packet->SerializeAsString();
						this->socket().send(boost::asio::buffer(built_response.c_str(), built_response.length()));
                    
						delete response_packet;
						response_packet = 0;
					}
					else
					{
						std::cout << "No handler found for service_id: " <<
							(uint32_t)request_packet.header().service_id() 
							<< " method_id: " << (uint32_t)request_packet.header().method_id() << std::endl;
					}
				}
            
				this->socket_.async_receive(boost::asio::buffer(this->buffer_, 2048),
					boost::bind(&ServerClient::Receive, this, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				std::cout << "Client: " << error.message() << std::endl;
            
				// Remove ourselves
				this->io_service_.post(boost::bind(&Server::RemoveServerClient, &this->server_, this));
			}
		}
    
		boost::asio::io_service &ServerClient::io_service()
		{
			return this->io_service_;
		}
    
		boost::asio::ip::tcp::socket &ServerClient::socket()
		{
			return this->socket_;
		}

		Server &ServerClient::server()
		{
			return this->server_;
		}
    
		Server::Server(boost::asio::io_service &io_service, const char *host, short port)
			: io_service_(io_service), endpoint_(boost::asio::ip::address::from_string(host), port),
				acceptor_(io_service)
		{
		}
    
		bool Server::Init()
		{   
			// Initialize socket
			this->acceptor_.open(this->endpoint_.protocol());
			this->acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			this->acceptor_.bind(this->endpoint_);
			this->acceptor_.listen();
        
			ServerClient *pending_client = new ServerClient(this->io_service_, *this);
			this->acceptor_.async_accept(pending_client->socket(),
				boost::bind(&Server::Accept, this, _1, pending_client));
        
			return true;
		}
    
		void Server::Accept(const boost::system::error_code &error, ServerClient *pending_client)
		{
			if (!error)
			{
				pending_client->Start();
				this->server_clients_.insert(pending_client);
				ServerClient *new_pending_client = new ServerClient(this->io_service_, *this);
				this->acceptor_.async_accept(new_pending_client->socket(),
					boost::bind(&Server::Accept, this, _1, new_pending_client));
			}
		}
    
		boost::asio::io_service &Server::io_service()
		{
			return this->io_service_;
		}
    
		std::set<ServerClient *> &Server::server_clients()
		{
			return this->server_clients_;
		}
    
		Services::BoundServicesManager &Server::services_manager()
		{
			return this->services_manager_;
		}
    
		void Server::RemoveServerClient(ServerClient *server_client)
		{
			std::set<ServerClient *>::iterator iter = this->server_clients_.find(server_client);
			if (iter != this->server_clients_.end())
			{
				(*iter)->socket().close();
            
				delete *iter;
				this->server_clients_.erase(iter);
			}
		}
	}
}

