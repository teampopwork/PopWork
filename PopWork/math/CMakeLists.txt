# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	mtrand.cpp
	mtrand.h
	point.h
	rect.h
	popmatrix.cpp
	popmatrix.h
	ratio.cpp
	ratio.h
	popvector.h
	trivertex.h
)