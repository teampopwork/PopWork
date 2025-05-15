# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../../lib/stb_image
	../
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	STB_IMAGE_IMPLEMENTATION
    STBI_MSC_SECURE_CRT
    STB_IMAGE_WRITE_IMPLEMENTATION
)

target_sources(${PROJECT_NAME} PRIVATE
	imagelib.cpp
	imagelib.h
)