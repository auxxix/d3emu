#include <time.h>

#include "Net/Server.h"

#include "Services/BaseService.h"
#include "Services/AuthenticationService.h"
#include "Services/ChannelInvitationService.h"
#include "Services/UserManagerService.h"
#include "Services/GameMasterService.h"
#include "Services/FollowersService.h"
#include "Services/FriendsService.h"
#include "Services/PresenceService.h"
#include "Services/StorageService.h"
#include "Services/ToonExternalService.h"

int main(int argc, char **argv)
{
	srand((unsigned int)time(0));
    
    boost::asio::io_service io_service;
    d3emu::Net::Server server(io_service, "127.0.0.1", 6543);

    if (server.Init())
    {
		// Initialize services
        server.services_manager().Bind(new d3emu::Services::AuthenticationService(0x0DECFC01, 0));
        server.services_manager().Bind(new d3emu::Services::ChannelInvitationService(0x83040608, 0));
        server.services_manager().Bind(new d3emu::Services::UserManagerService(0x3E19268A, 0));
        server.services_manager().Bind(new d3emu::Services::GameMasterService(0x810CB195, 0));
        server.services_manager().Bind(new d3emu::Services::ToonExternalService(0x4124C31B, 0));
        server.services_manager().Bind(new d3emu::Services::FollowersService(0xE5A11099, 0));
        server.services_manager().Bind(new d3emu::Services::FriendsService(0xA3DDB1BD, 0));
        server.services_manager().Bind(new d3emu::Services::PresenceService(0xFA0796FF, 0));
        server.services_manager().Bind(new d3emu::Services::StorageService(0xDA6E4BB9, 0,
			new d3emu::Services::StorageDatabaseEngine()));

        boost::system::error_code ec;
        do {
            io_service.run(ec);
        } while (!ec);
    }
    
	return 0;
}
