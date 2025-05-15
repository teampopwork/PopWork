# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	descparser.cpp
	descparser.h
	modval.cpp
	modval.h
	xmlparser.cpp
	xmlparser.h
	xmlwriter.cpp
	xmlwriter.h
)