#include <GaiaSharedMemory/GaiaSharedMemory.hpp>
#include <iostream>
#include <string>
#include <cstring>

using namespace Gaia::SharedMemory;

int main()
{
    SharedPool pool;
    pool.Open("Test Variable");

    SharedVariable<int> shared_integer(pool);
    shared_integer.Locate("Test Integer");

    auto a1 = shared_integer.Access();

    (shared_integer.Access())++;

    auto a2 = shared_integer.Access();

    (shared_integer.Access())++;

    auto a3 = shared_integer.Access();

    return 0;
}