#include "SourceMemory.hpp"

namespace Gaia::SharedMemory
{
    /// Create a piece of shared memory block.
    void SourceMemory::Create(const std::string &name, long size)
    {
        MemoryObject = std::make_unique<boost::interprocess::shared_memory_object>(
                boost::interprocess::open_or_create, name.c_str(),
                boost::interprocess::read_write);
        MemoryObject->truncate(size);
        MappedRegion = std::make_unique<boost::interprocess::mapped_region>(
                *MemoryObject,
                boost::interprocess::read_write);
    }

    /// Remove the created shared memory.
    void SourceMemory::Delete()
    {
        if (MemoryObject)
        {
            boost::interprocess::shared_memory_object::remove(MemoryObject->get_name());
        }
    }

    /// Reset all the bytes of the linked shared memory to zero.
    void SourceMemory::Clear()
    {
        if (MappedRegion)
        {
            std::memset(MappedRegion->get_address(), 0, MappedRegion->get_size());
        }
    }

    /// Destructor
    SourceMemory::~SourceMemory()
    {
        Delete();
    }

    /// Get the address of this memory region.
    char *SourceMemory::GetPointer() const
    {
        if (MappedRegion)
        {
            return static_cast<char*>(MappedRegion->get_address());
        }
        return nullptr;
    }

    /// Get the total size of this memory region.
    std::size_t SourceMemory::GetSize() const
    {
        if (MappedRegion)
        {
            return MappedRegion->get_size();
        }
        return 0;
    }
}