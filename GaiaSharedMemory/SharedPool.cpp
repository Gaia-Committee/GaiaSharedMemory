#include "SharedPool.hpp"

namespace Gaia::SharedMemory
{
    /// Open a existing block of shared memory.
    void SharedPool::Open(const std::string &name)
    {
        ManagedMemoryObject = std::make_unique<boost::interprocess::managed_shared_memory>
                (boost::interprocess::open_only, name.c_str());
        OwnedMemory = false;
        MemoryName = name;
    }

    /// Unlink the current linked shared memory.
    void SharedPool::Close()
    {
        ManagedMemoryObject.reset(nullptr);
        OwnedMemory = false;
        MemoryName = "";
    }

    /// Create a block of shared memory and open it.
    void SharedPool::Create(const std::string &name, long size)
    {
        if (ManagedMemoryObject && OwnedMemory)
        {
            Delete();
        }
        boost::interprocess::shared_memory_object::remove(name.c_str());
        ManagedMemoryObject = std::make_unique<boost::interprocess::managed_shared_memory>
                (boost::interprocess::create_only, name.c_str(), size);
        OwnedMemory = true;
        MemoryName = name;
    }

    /// Destroy the shared memory and free its memory.
    void SharedPool::Delete() noexcept
    {
        if (!MemoryName.empty())
        {
            boost::interprocess::shared_memory_object::remove(MemoryName.c_str());
        }
    }
}