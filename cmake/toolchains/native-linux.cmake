# native-linux.cmake
#
# Toolchain file for a native (non-cross-compiled) Linux build.

set(CMAKE_SYSTEM_NAME Linux)

if (NOT CMAKE_CXX_COMPILER)
    message(WARNING "CMAKE_CXX_COMPILER not set, defaulting to g++")
    set(CMAKE_CXX_COMPILER g++)

endif()

add_compile_definitions(PLATFORM_LINUX)