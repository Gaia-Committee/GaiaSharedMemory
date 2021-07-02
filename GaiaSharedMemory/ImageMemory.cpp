#include "ImageMemory.hpp"

namespace Gaia::SharedMemory
{
    /// Open the existed shared memory block.
    void ImageMemory::Open(const std::string &name)
    {
        MemoryObject = std::make_unique<boost::interprocess::shared_memory_object>(
                boost::interprocess::open_only, name.c_str(),
                boost::interprocess::read_only);
        MappedRegion = std::make_unique<boost::interprocess::mapped_region>(
                *MemoryObject, boost::interprocess::read_only);
    }

    /// Close the open shared memory block.
    void ImageMemory::Close()
    {
        MappedRegion.reset(nullptr);
        MemoryObject.reset(nullptr);
    }

    /// Get the address of this memory region.
    char *ImageMemory::GetPointer() const
    {
        if (MappedRegion.operator bool())
        {
            return static_cast<char*>(MappedRegion->get_address());
        }
        return nullptr;
    }

    /// Get the total size of this memory region.
    std::size_t ImageMemory::GetSize() const
    {
        if (MappedRegion.operator bool())
        {
            return MappedRegion->get_size();
        }
        return 0;
    }
}