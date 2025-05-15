cmake_minimum_required(VERSION 3.18)

project(Hun-garr)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	GameApp.cpp
	Board.cpp
	TitleScreen.cpp
	OptionsDialog.cpp
	LevelupEffect.cpp
	GameOverEffect.cpp

	# Headers
	GameApp.h
	Board.h
	TitleScreen.h
	OptionsDialog.h
	LevelupEffect.h
	GameOverEffect.h
	
	../Res.h
	../Res.cpp
)

add_executable(Hun-garr ${SRC_MAIN})
add_dependencies(Hun-garr SexyAppFramework)
target_link_libraries(Hun-garr SexyAppFramework)
