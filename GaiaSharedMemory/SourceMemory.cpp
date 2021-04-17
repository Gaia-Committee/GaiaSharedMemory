#include "SourceMemory.hpp"

namespace Gaia::SharedMemory
{
    /// Create a piece of shared memory block.
    void SourceMemory::Create(const std::string &name, long size)
    {
        boost::interprocess::shared_memory_object::remove(name.c_str());
        MemoryObject = std::make_unique<boost::interprocess::shared_memory_object>(
                boost::interprocess::create_only, name.c_str(),
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

    /// Get the pointer of the first byte of the shared memory and its total size.
    ByteUtility::BytesAddress SourceMemory::GetBytesAddress()
    {
        Exceptions::AssertFailure::ThrowIfNot(MappedRegion.operator bool(),
                                              "shared memory is open");
        return ByteUtility::BytesAddress(
                static_cast<unsigned char*>(MappedRegion->get_address()), MappedRegion->get_size());
    }

    /// Destructor
    SourceMemory::~SourceMemory()
    {
        Delete();
    }
}