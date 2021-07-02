#==============================
# Requirements
#==============================

cmake_minimum_required(VERSION 3.10)

#==============================
# Project Settings
#==============================

if (NOT PROJECT_DECLARED)
    project("Gaia Shared Memory" LANGUAGES CXX VERSION 0.9)
    set(PROJECT_DECLARED)
endif()

#==============================
# Project Modules
#==============================

add_subdirectory("GaiaSharedMemory")
if (WITH_TEST)
    add_subdirectory("TestImage")
    add_subdirectory("TestSource")

    add_subdirectory("TestVariableHolder")
    add_subdirectory("TestVariableVisitor")
endif()