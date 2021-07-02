#include <GaiaSharedMemory/GaiaSharedMemory.hpp>
#include <iostream>
#include <string>
#include <cstring>

using namespace Gaia::SharedMemory;

int main()
{
    boost::interprocess::shared_memory_object::remove("Test Variable");

    SharedPool pool;
    pool.Create("Test Variable", 1024);

    SharedVariable<int> shared_integer(pool);
    shared_integer.Construct("Test Integer");

    *shared_integer = 3;

    auto a1 = *shared_integer;

    (*shared_integer)++;

    auto a2 = *shared_integer;

    (*shared_integer)++;

    auto a3 = *shared_integer;

    return 0;
}