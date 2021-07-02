#pragma once

#include <string>
#include <memory>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace Gaia::SharedMemory
{
    /**
     * @brief Use this class to alloc a piece of shared memory and directly read or write bytes into it.
     * @details
     *  This class use 'open or create' mode to open the shared memory block and use 'read and write' mode to access
     *  its content.
     */
    class SourceMemory
    {
    protected:
        /// Object for controlling the shared memory.
        std::unique_ptr<boost::interprocess::shared_memory_object> MemoryObject;
        /// Object for accessing the content of the shared memory.
        std::unique_ptr<boost::interprocess::mapped_region> MappedRegion;

    public:
        /// Destructor, will automatically remove the shared memory if it exists.
        ~SourceMemory();

        /**
         * @brief Create a piece of shared memory block.
         * @param name The name of it, and other applications can use this name to find it.
         * @param size The size of the total block.
         * @details
         *  This function will remove the previous shared memory of the same name if it exists,
         *  in order to handle the situation when shared memory block is created by broken programs and
         *  too less to use.
         */
        void Create(const std::string& name, long size);
        /**
         * @brief Remove the created shared memory.
         * @pre Shared memory is created and open.
         */
        void Delete();

        /**
         * @brief Reset all the bytes of the linked shared memory to zero.
         */
        void Clear();

        /// Get the pointer of this memory region.
        [[nodiscard]] char* GetPointer() const;
        /// Get the total size of this memory region.
        [[nodiscard]] std::size_t GetSize() const;
    };
}