cmake_minimum_required(VERSION 3.15)
project(dupHunter CXX)

# Make our helper functions available to this and any nested CMakeLists.txt
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
include(helpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Library: the exception lib ----
add_library(file_reader_lib
    source/file_reader.cpp
    source/argument_parser.cpp
)

target_include_directories(file_reader_lib PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

project_set_target_warnings(file_reader_lib)

# ---- Executable: demo / entry point ----
add_executable(${PROJECT_NAME}_app
    source/duplicate_hunter.cpp
)
target_link_libraries(${PROJECT_NAME}_app PRIVATE file_reader_lib)
project_set_target_warnings(${PROJECT_NAME}_app)

# ---- Install rules ----
install(TARGETS file_reader_lib ${PROJECT_NAME}_app
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)