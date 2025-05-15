# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	buffer.cpp
	buffer.h
	autocrit.h
	critsect.h
	flags.cpp
	flags.h
	httptransfer.cpp
	httptransfer.h
	keycodes.cpp
	keycodes.h
	profile.cpp
	profile.h
	smartptr.h
)