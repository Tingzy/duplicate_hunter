# native-windows.cmake

set(CMAKE_SYSTEM_NAME Windows)

# Use the MSVC toolset that's already on PATH (e.g. via a Developer
# Command Prompt / vcvarsall.bat); nothing to locate manually.

add_compile_definitions(PLATFORM_WINDOWS)