# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	mtrand.cpp
	mtrand.h
	point.h
	rect.h
	sexymatrix.cpp
	sexymatrix.h
	ratio.cpp
	ratio.h
	sexyvector.h
	trivertex.h
)