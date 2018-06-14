cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# name and version of the project
project(fatx VERSION 0.0.1 LANGUAGES C)

# diverse flags and cmake path variables
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall --pedantic -g")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# we need fuse
find_package(FUSE REQUIRED)
include_directories(${FUSE_INCLUDE_DIR})


# our target executable and the main file
add_executable(fatx fatx_main.c)
target_link_libraries(fatx ${FUSE_LIBRARIES})

add_subdirectory(src)
target_include_directories(fatx PRIVATE include)

