#ifndef _IP_ALLOCATOR_INTERFACE_HPP_
#define _IP_ALLOCATOR_INTERFACE_HPP_

#include <cstdint>
#include <optional>

class IIPAllocator
{
public:
    virtual ~IIPAllocator() = default;

    virtual std::optional<std::uint32_t> assign_free_ip(std::uint64_t mac) = 0;
    virtual void refresh_lease_timeout(std::uint64_t mac) = 0;
    virtual void release_ip(std::uint64_t mac) = 0;
    virtual void garbage_collector() = 0;
};


#endif
