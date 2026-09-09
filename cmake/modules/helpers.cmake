# helpers.cmake
#
# Small collection of shared helper functions for this project's CMake
# build.
 
# Enables a sensible, portable set of compiler warnings on <target>.
add_compile_definitions(XXH_INLINE_ALL)

function(project_set_target_warnings target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()