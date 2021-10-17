cmake_minimum_required (VERSION 3.8)

project(core)

file(GLOB CORE_SOURCE "src/*.cpp" "include/*.h")

add_library (core SHARED ${CORE_SOURCE})
