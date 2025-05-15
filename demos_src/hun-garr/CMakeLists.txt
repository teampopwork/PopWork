# CMakeLists.txt
project(Hun-garr)

set(SOURCES
	# Sources
	main.cpp
	gameapp.cpp
	board.cpp
	titlescreen.cpp
	optionsdialog.cpp
	levelupeffect.cpp
	gameovereffect.cpp

	# Headers
	gameapp.h
	board.h
	titlescreen.h
	optionsdialog.h
	levelupeffect.h
	gameovereffect.h
	
	../res.h
	../res.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	../../
)

target_link_libraries(${PROJECT_NAME} PopWork)
