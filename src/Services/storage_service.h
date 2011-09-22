#ifndef D3EMU_STORAGESERVICE_H
#define D3EMU_STORAGESERVICE_H

#include "service/storage/storage.pb.h"

#include "service.h"

namespace d3emu
{
	namespace services
	{
		// TODO: Create base class that is agnostic between underlying database engines. This will
		//		allow developers to use any type of database engine.
		class StorageDatabaseEngine
		{
		public:
			// Is passing Client appropriate here? We'll need to do a bit more research to determine
			// what actually needs to be passed...
			bool GetGameAccountSettings(Client &client, bnet::protocol::storage::ExecuteResponse &response);
		};

		class StorageService : public Service
		{
		public:
			StorageService(uint32_t service_hash, uint8_t service_id);

			// NOTE: Ownership of database_engine will be transferred to StorageService.
			StorageService(uint32_t service_hash, uint8_t service_id, StorageDatabaseEngine *database_engine);
			~StorageService();

			net::PacketResponse *Request(Client &client, net::PacketRequest &packet);
			std::string Name() const;

			bool has_database_engine();
			void set_database_engine(StorageDatabaseEngine *database_engine);
			StorageDatabaseEngine *database_engine();

		private:
			StorageDatabaseEngine *database_engine_;
			bool has_database_engine_;

			void set_has_database_engine();
			void clear_has_database_engine();

			// 0x01
			net::PacketResponse *ExecuteRequest(Client &client, net::PacketRequest &packet);

			// 0x02
			net::PacketResponse *OpenTableRequest(Client &client, net::PacketRequest &packet);

			// 0x03
			net::PacketResponse *OpenColumnRequest(Client &client, net::PacketRequest &packet);
		};
	}
}

#endif
