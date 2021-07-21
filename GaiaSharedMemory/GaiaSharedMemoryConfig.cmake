cmake_minimum_required(3.10)

find_path(GaiaSharedMemory_INCLUDE_DIRS "GaiaSharedMemory")
find_library(GaiaSharedMemory_LIBS "GaiaSharedMemory")

if (GaiaSharedMemory_INCLUDE_DIRS AND GaiaSharedMemory_LIBS)
    set(GaiaSharedMemory_FOUND TRUE)
endif()