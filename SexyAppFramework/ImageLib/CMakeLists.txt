target_sources(${PROJECT_NAME} PRIVATE
	ImageLib.cpp
	ImageLib.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ../../lib/stb_image)