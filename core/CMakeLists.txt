
cmake_minimum_required (VERSION 3.8)

project ("core")

set( SOURCE_LIB 
	"src/startup.cpp"
)		

add_library(core_lib SHARED ${SOURCE_LIB})
