# CMake setup based on the Csound opcode SDK repo
# https://github.com/csound/opcode_sdk

cmake_minimum_required(VERSION 3.5)
project(tuning)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# switch RPATH use off
set(CMAKE_MACOSX_RPATH 0)
# force make to print the command lines
set(CMAKE_VERBOSE_MAKEFILE on)
# path to Csound cmake module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
"${CMAKE_SOURCE_DIR}/cmake/Modules/")
# set C++ compilation flags
set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS}  "-std=c++11")

# Csound opcode build
find_package(CSOUND)

if(CSOUND_FOUND)
  message(STATUS "Building Opcodes")
  if(APPLE)
        add_library(tuning SHARED src/tuning.cpp)
    else()
        add_library(tuning MODULE src/tuning.cpp)
  endif()
  target_sources(tuning PRIVATE src/libs/MTS-ESP/Client/libMTSClient.cpp)
  target_include_directories(tuning PRIVATE
    ${CSOUND_INCLUDE_DIRS}
    src/libs/tuning-library/include
    src/libs/MTS-ESP/Client)
  target_compile_options(tuning PRIVATE "-Wno-write-strings")
else()
  message(STATUS "Csound installation not found")
endif()
