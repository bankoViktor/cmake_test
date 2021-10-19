cmake_minimum_required (VERSION 3.8)

project(core)



add_library (core SHARED
	"src/WinSock.cpp"
	"src/Utils.cpp"
	"src/HttpInterface.cpp"
	"src/HttpInterfaceConfigurator.cpp"
	"src/HttpRequest.cpp"
	"src/HttpResponse.cpp"
	"src/HttpHeader.cpp"
	"src/HttpHeaderCollection.cpp"
	"src/HttpMethods.cpp"
)

target_compile_options (core PRIVATE 
	/std:c++20
	/utf-8
)

target_link_options (core PRIVATE
	/SUBSYSTEM:CONSOLE
)
