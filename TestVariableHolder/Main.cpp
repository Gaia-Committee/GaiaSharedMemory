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

    shared_integer.Access() = 3;

    auto a1 = shared_integer.Access();

    (shared_integer.Access())++;

    auto a2 = shared_integer.Access();

    (shared_integer.Access())++;

    auto a3 = shared_integer.Access();

    return 0;
}