# A CMake toolchain file for cross-compiling for PPC VxWorks.
#
# You need to pick the type of build files that CMake generates (the Generator). If you have a
# build system already that uses GNU Make, or are building on a macOS or Unix-based host,
# "Unix Makefiles" will cover most cases. On Windows, you need to use a non-Visual-Studio generator.
# This requires you to have some kind of non-VS build system installed. Some options are:
# - MinGW64 (must be available on PATH)
# - Strawberry Perl (use 'Unix Makefiles' generator)
# - NMake (comes with VS, but must be in a developer command prompt)
#
# Usage: cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=path/to/this/file ..

# Setting these names causes CMake to look in the Platform subdirectory for files called:
# Platform/VxWorks.cmake
# Platform/VxWorks-PPC.cmake
set(CMAKE_SYSTEM_NAME VxWorks)
set(CMAKE_SYSTEM_PROCESSOR PPC)

# Set this to the location of the Platform subdirectory containing the platform files.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})




if(NOT ${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
  message(FATAL_ERROR "VxWorks is tested on Windows-only currently.")
endif()

# The IAR installation directory, highly likely to require customization
set(VXWORKS_INSTALL_DIR "C:/WindRiver" CACHE STRING "The Wind River install directory")

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  ${VXWORKS_INSTALL_DIR}/vxworks-6.8)

set(CMAKE_C_COMPILER ${VXWORKS_INSTALL_DIR}/wrenv.exe CACHE FILEPATH "VxWorks C Compiler")
set(CMAKE_CXX_COMPILER ${VXWORKS_INSTALL_DIR}/wrenv.exe CACHE FILEPATH "VxWorks C++ Compiler")

# This tells CMake to use a static library program to do its minimal compiler
# test instead of an executable - this translates well to embedded toolchains.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# If that doesn't work, you might need to comment the line above and uncomment
# this line to bypass the compiler checks.
# set(CMAKE_C_COMPILER_WORKS 1)
# set(CMAKE_CXX_COMPILER_WORKS 1)