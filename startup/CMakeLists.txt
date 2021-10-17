cmake_minimum_required (VERSION 3.8)

project(startup)

file(GLOB STARTUP_SOURCE "src/*.cpp" "include/*.h")

add_library (startup SHARED ${STARTUP_SOURCE})

target_link_libraries(startup core)
