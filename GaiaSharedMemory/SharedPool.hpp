#pragma once

#include <string>
#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace Gaia::SharedMemory
{
    /// Memory manager for defining custom memory allocator
    using SharedPoolMemoryManager = boost::interprocess::managed_shared_memory::segment_manager;

    /**
     * @brief Shared pool for constructing and finding shared variables.
     */
    class SharedPool
    {
        template<typename VariableType>
        friend class SharedVariable;

    protected:
        /// Whether this instance owned the shared memory or not.
        bool OwnedMemory {false};
        /// Shared memory object which is auto-managed.
        std::unique_ptr<boost::interprocess::managed_shared_memory> ManagedMemoryObject;

    private:
        /// Name of the created shared memory.
        std::string MemoryName;

    public:
        /**
         * @brief Open a existing block of shared memory.
         * @param name The name of the shared memory to open.
         * @throw boost::interprocess::interprocess_exception If failed to open the given shared memory.
         */
        void Open(const std::string &name);
        /// Unlink the current linked shared memory.
        void Close();

        /**
         * @brief Create a block of shared memory and open it.
         * @param name The name of the shared memory to create and open.
         * @param size The size of the shared memory to create.
         * @throw boost::interprocess::interprocess_exception If failed to create or open the shared memory.
         * @details
         *  If the shared memory of the same name already exists, this function will remove the previous shared memory
         *  of the same name.
         */
        void Create(const std::string &name, long size);
        /// Destroy the shared memory and free its memory.
        void Delete() noexcept;
    };
}