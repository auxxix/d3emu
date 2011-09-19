#include "Service.h"
#include "BaseService.h"

#include <iostream>

namespace d3emu
{
    BoundServicesManager::BoundServicesManager()
    {
        this->bound_services_ = new BoundServicesMap();
        this->bound_services_hashes_ = new BoundServicesHashMap();
        
        // Bind BaseService
        BaseService *base_service = new BaseService(0, 0);
        base_service->set_manager(this);
        this->bound_services_->insert(BoundServicePair(0, base_service));
        this->bound_services_hashes_->insert(BoundServiceHashPair(0, 0));
    }

    BoundServicesManager::~BoundServicesManager()
    {
        // Deallocate services since we are the owner
        for (BoundServicesMap::iterator iter = this->bound_services_->begin();
            iter != this->bound_services_->end();)
        {
            Service *service = iter->second;
            this->bound_services_->erase(iter++);
            delete service;
        }

        delete this->bound_services_;
        delete this->bound_services_hashes_;
    }

    uint8_t BoundServicesManager::Bind(Service *service)
    {
        service->set_manager(this);

        // We'll use Service::service_id() as a suggestion of the new_service_id, but
        // if it already exists in the bound_services list, we'll have to use a new one
        uint8_t new_service_id = service->service_id();
        while (this->bound_services_->find(new_service_id) != 
            this->bound_services_->end())
            new_service_id++;

        service->set_service_id(new_service_id);

        this->bound_services_->insert(BoundServicePair(new_service_id, service));
        this->bound_services_hashes_->insert(BoundServiceHashPair(service->service_hash(), new_service_id));

        return new_service_id;
    }

    int BoundServicesManager::Size() const
    {
        return (int)this->bound_services_->size();
    }

    uint8_t BoundServicesManager::bound_service_id(uint32_t service_hash)
    {
        BoundServicesHashMap::iterator iter =
            this->bound_services_hashes_->find(service_hash);

        uint8_t service_id = 0;
        if (iter != this->bound_services_hashes_->end())
            service_id = iter->second;

        return service_id;
    }

    Service *BoundServicesManager::bound_service(uint8_t service_id)
    {
        BoundServicesMap::iterator iter =
            this->bound_services_->find(service_id);

        Service *service = 0;
        if (iter != this->bound_services_->end())
            service = iter->second;

        return service;
    }

    BoundServicesMap *BoundServicesManager::mutable_bound_services()
    {
        return this->bound_services_;
    }

    BoundServicesHashMap *BoundServicesManager::mutable_bound_services_hashes()
    {
        return this->bound_services_hashes_;
    }
    
    // Service

    Service::Service(uint32_t _service_hash, uint8_t _service_id)
        : service_hash_(_service_hash), service_id_(_service_id), manager_(0)
    {
    }

    void Service::Request(Client &client, PacketRequest &request)
    {
        std::cout << "Unknown request for service_id " << std::hex << std::uppercase
            << ((uint32_t)request.header().service_id() & 0xff) << std::endl;
    }

    uint8_t Service::service_id() const
    {
        return this->service_id_;
    }

    void Service::set_service_id(uint8_t service_id)
    {
        this->service_id_ = service_id;
    }

    uint32_t Service::service_hash() const
    {
        return this->service_hash_;
    }

    void Service::set_service_hash(uint32_t hash)
    {
        this->service_hash_ = hash;
    }

    void Service::set_manager(BoundServicesManager *manager)
    {
        this->manager_ = manager;
    }

    BoundServicesManager *Service::manager() const
    {
        return this->manager_;
    }

    BoundServicesManager *Service::mutable_manager()
    {
        return this->manager_;
    }

    std::string Service::Name() const
    {
        return std::string("d3emu::Service");
    }
}