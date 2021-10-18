cmake_minimum_required (VERSION 3.8)

project(core)

add_library (core SHARED ${CORE_SOURCE}
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
