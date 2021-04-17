#pragma once

#include <string>
#include <type_traits>
#include <boost/interprocess/managed_shared_memory.hpp>
#include "SharedPool.hpp"

namespace Gaia::SharedMemory
{
    /**
     * @brief This class is designed for maintain and access the variables in the shared memory blocks.
     * @tparam VariableType The type of the variable.
     * @details
     *  Pay attention to that this class does not guarantee the multi-thread safety. Usually plain-data-type variables
     *  and non-blocking multi-thread containers are suitable.
     */
    template<typename VariableType>
    class SharedVariable
    {
    protected:
        /// Host shared memory pool which holds the shared variable of this instance.
        SharedPool& HostPool;
        /// Pointer to the shared variable in the shared memory.
        VariableType* VariablePointer {nullptr};
        /// The name used to find the shared variable in the shared memory.
        std::string VariableName;

    public:
        /// Constructor, will bind itself to a SharedPool.
        explicit SharedVariable(SharedPool& pool) : HostPool(pool)
        {}

        /// Destructor, will automatically remove the shared variable if it exists.
        virtual ~SharedVariable()
        {
            Destruct();
        }

        /// Get the address of the shared variable in the shared memory block.
        [[nodiscard]] VariableType* GetAddress() const
        {
            return VariablePointer;
        }

        /// Access the object pointed by the pointer as an object reference.
        VariableType& Access()
        {
            Exceptions::NullPointerException::ThrowIfNull(VariablePointer, "VariablePointer");
            return *VariablePointer;
        }

        /// Access the member of the object if it's a pointer.
        template<typename = typename std::enable_if<std::is_pointer_v<VariableType>>>
        VariableType* operator->()
        {
            return VariablePointer;
        }

        /// Dereference the pointer into an object reference if it's a pointer.
        template<typename = typename std::enable_if<std::is_pointer_v<VariableType>>>
        VariableType& operator*()
        {
            return *VariablePointer;
        }

        /**
         * @brief Construct an instance in the shared memory.
         * @tparam ConstructorArguments
         * @param name The name of the object for searching and locating it.
         * @param arguments Arguments for constructor.
         * @throw boost::interprocess::interprocess_exception If failed to construct a instance of the given type in
         *                                                    the shared memory.
         */
        template<typename... ConstructorArguments>
        void Construct(const std::string& name, ConstructorArguments... arguments)
        {
            if (VariablePointer)
            {
                Destruct();
            }
            VariablePointer = HostPool.ManagedMemoryObject->construct<VariableType>(name.c_str())(arguments...);
        }

        /**
         * @brief Call the destructor of the shared variable and destroy the named object in the shared pool.
         * @throw boost::interprocess::interprocess_exception If failed to destruct the named object.
         */
        void Destruct()
        {
            if (VariablePointer)
            {
                VariablePointer->~VariableType();
                VariablePointer = nullptr;
            }
            if (!VariableName.empty())
            {
                HostPool.ManagedMemoryObject->destroy<VariableType>(VariableName.c_str());
                VariableName.clear();
            }
        }

        /// Locate this shared variable according to the given name in the bound shared object pool.
        void Locate(const std::string& name) noexcept
        {
            auto [pointer, size] = HostPool.ManagedMemoryObject->find<VariableType>(name.c_str());
            VariablePointer = pointer;
        }
    };
}