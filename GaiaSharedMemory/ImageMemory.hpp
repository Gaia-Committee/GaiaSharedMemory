#pragma once

#include <string>
#include <memory>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace Gaia::SharedMemory
{
    /**
     * @brief This class is used to read-only access a existed shared memory block and read bytes from it.
     * @details
     *  Usually instances of this class are used to read bytes from shared memory blocks created by instances of
     *  SourceMemory. In producer-consumer model, SourceMemory is the producer and ImageMemory is the consumer.
     */
    class ImageMemory
    {
    protected:
        /// Object for controlling the shared memory.
        std::unique_ptr<boost::interprocess::shared_memory_object> MemoryObject;
        /// Object for accessing the content of the shared memory.
        std::unique_ptr<boost::interprocess::mapped_region> MappedRegion;

    public:
        /**
         * @brief Open the existed shared memory block.
         * @param name The name of the shared memory block to open.
         * @throw boost::interprocess::interprocess_exception If the given shared memory dose not exist.
         */
        void Open(const std::string& name) noexcept(false);
        /// Close the open shared memory block.
        void Close();

        /// Get the address of this memory region.
        [[nodiscard]] char* GetPointer() const;
        /// Get the total size of this memory region.
        [[nodiscard]] std::size_t GetSize() const;
    };
}