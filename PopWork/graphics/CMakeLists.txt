# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PRIVATE
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	color.cpp
	color.h
	font.cpp
	font.h
	graphics.cpp
	graphics.h
	image.cpp
	image.h
	imagefont.cpp
	imagefont.h
	memoryimage.cpp
	memoryimage.h
	nativedisplay.cpp
	nativedisplay.h
	quantize.cpp
	quantize.h
	sdlimage.cpp
	sdlimage.h
	sdlinterface.cpp
	sdlinterface.h
	sharedimage.cpp
	sharedimage.h
	SysFont.cpp
	SysFont.h
	SWTri/SWTri.cpp
	SWTri/SWTri.h

	HeaderFont/LiberationSansRegular.h
)