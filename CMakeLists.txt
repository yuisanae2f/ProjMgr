cmake_minimum_required(VERSION 3.10)
project(ProjMgr)

add_executable(
	${PROJECT_NAME}
	"src/main.cpp"
	"include/ProjMgr/Screen.h"
	"src/xScreen.cpp"
	"include/ProjMgr/Err.h"
	"include/ProjMgr/Project.h"
	"src/xProject.cpp"
	"include/ProjMgr/MemMap.h"
	"src/xMemMap.cpp"
	"include/ProjMgr/Selection.h"
	"src/xSelection.cpp"
	"include/ProjMgr/Programme.h"
	"src/main.manage.cpp"
	"src/xProgramme.cpp"

	"include/ProjMgr/FileState.h"
	)

include_directories(include)