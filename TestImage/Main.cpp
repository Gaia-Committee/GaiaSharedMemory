#include <GaiaSharedMemory/GaiaSharedMemory.hpp>
#include <iostream>
#include <string>

using namespace Gaia::SharedMemory;

int main()
{
    ImageMemory image;
    image.Open("Test String");

    std::cout << image.GetBytesAddress().Data << std::endl;

    return 0;
}