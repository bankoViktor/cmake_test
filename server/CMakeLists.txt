cmake_minimum_required (VERSION 3.8)

project(server)

file(GLOB SERVER_SOURCE "src/*.cpp" "include/*.h")

add_executable (server ${SERVER_SOURCE})

target_link_libraries(server core)