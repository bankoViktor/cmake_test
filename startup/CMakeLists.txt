
cmake_minimum_required (VERSION 3.8)

project ("startup")

include(ExternalProject)

ExternalProject_Add(nlohmann
  GIT_REPOSITORY    https://github.com/nlohmann/json.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/nlohmann-src"
  BINARY_DIR        "${CMAKE_BINARY_DIR}/nlohmann-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

set(SOURCE_LIB 
	"src/startup.cpp"
)

add_library(startup SHARED ${SOURCE_LIB})

# https://docs.conan.io/en/latest/getting_started.html