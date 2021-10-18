cmake_minimum_required (VERSION 3.8)

project ("cmake_test")

set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")

message("OUTPUT: " ${OUTPUT_DIRECTORY})

add_subdirectory(core)
add_subdirectory(startup)
add_subdirectory(server)
