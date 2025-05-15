# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PRIVATE
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	debug.cpp
	debug.h
	perftimer.cpp
	perftimer.h
	memmgr.h
)