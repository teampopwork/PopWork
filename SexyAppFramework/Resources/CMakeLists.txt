# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	propertiesparser.cpp
	propertiesparser.h
	resourcemanager.cpp
	resourcemanager.h
)