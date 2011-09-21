#ifndef D3EMU_SERVICE_H
#define D3EMU_SERVICE_H

#include <stdint.h>
#include <map>
#include <string>

#include "Client.h"
#include "../Net/Packet.h"

namespace d3emu
{
	namespace Services
	{
		class Service;

		typedef std::pair<uint32_t, uint8_t> BoundServiceHashPair;
		typedef std::pair<uint8_t, Service *> BoundServicePair;

		typedef std::map<uint32_t, uint8_t> BoundServicesHashMap;
		typedef std::map<uint8_t, Service *> BoundServicesMap;

		class BoundServicesManager
		{
		public:
			BoundServicesManager();
			~BoundServicesManager();

			/**
			 * Returns service id on success, 0 on failure.
			 * Do NOT manually bind a BaseService!!!
			 */
			uint8_t Bind(Service *service);
			int Size() const;

			uint8_t bound_service_id(uint32_t service_hash);
			Service *bound_service(uint8_t service_id);

			BoundServicesMap *mutable_bound_services();
			BoundServicesHashMap *mutable_bound_services_hashes();

		private:
			BoundServicesMap *bound_services_;
			BoundServicesHashMap *bound_services_hashes_;
		};

		class Service
		{
		public:
			Service(uint32_t _service_hash, uint8_t _service_id);
        
			virtual PacketResponse *Request(Client &client, PacketRequest &request);

			uint8_t service_id() const;
			void set_service_id(uint8_t service_id);

			uint32_t service_hash() const;
			void set_service_hash(uint32_t hash);

			void set_manager(BoundServicesManager *manager);
			BoundServicesManager *manager() const;
			BoundServicesManager *mutable_manager();

			const char *current_packet() const;
			void set_current_packet(const char *packet, int length);

			int current_packet_length() const;

			virtual std::string Name() const;

		private:
			uint8_t service_id_;
			uint32_t service_hash_;
			BoundServicesManager *manager_;
		};
	} // Services namespace
} // d3emu namespace

#endif