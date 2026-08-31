cmake_minimum_required(VERSION 3.15)
project(dupHunter CXX)

# Make our helper functions available to this and any nested CMakeLists.txt
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
include(helpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Library: the file reader lib ----
add_library(file_reader_lib
    source/file_reader.cpp
    source/argument_parser.cpp
    source/file_comparator.cpp
    source/file_compare_buffer.cpp
    source/file_process_buffer.cpp
)

target_include_directories(file_reader_lib PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

project_set_target_warnings(file_reader_lib)

# ---- Library: the utilities lib ----
add_library(utilities_lib
    source/utilities/read_path_to_file.cpp
)

target_include_directories(utilities_lib PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

project_set_target_warnings(utilities_lib)

# ---- Executable: demo / entry point ----
add_executable(${PROJECT_NAME}_app
    source/duplicate_hunter.cpp
)
target_link_libraries(${PROJECT_NAME}_app PRIVATE file_reader_lib utilities_lib)
project_set_target_warnings(${PROJECT_NAME}_app)

# ---- Executable: utilities test ----
add_executable(utilities_test
    source/utilities_test.cpp
)
target_link_libraries(utilities_test PRIVATE  utilities_lib)
project_set_target_warnings(utilities_test)

# ---- Install rules ----
install(TARGETS file_reader_lib utilities_lib ${PROJECT_NAME}_app utilities_test
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)