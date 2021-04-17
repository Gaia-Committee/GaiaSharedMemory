#include <GaiaSharedMemory/GaiaSharedMemory.hpp>
#include <iostream>
#include <string>
#include <cstring>

using namespace Gaia::SharedMemory;

int main()
{
    SourceMemory source;
    source.Create("Test String", 60);

    std::string text;
    std::cin >> text;

    std::strcpy(reinterpret_cast<char *>(source.GetBytesAddress().Data), text.c_str());

    char key;
    std::cin >> key;

    return 0;
}