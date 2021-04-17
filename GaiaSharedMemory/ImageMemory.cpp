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

    /// Get the pointer of the first byte of the shared memory and its total size.
    ByteUtility::ConstBytesAddress ImageMemory::GetBytesAddress()
    {
        Exceptions::AssertFailure::ThrowIfNot(MappedRegion.operator bool(),
                                              "shared memory is open");
        return ByteUtility::ConstBytesAddress(
                static_cast<unsigned char const*>(MappedRegion->get_address()), MappedRegion->get_size());
    }
}