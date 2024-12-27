# Engine CMakeList.txt, "Author": Manzini Alessandro
# Engine specific logic here.
#
project("GameEngine")

# create library target
add_library("${PROJECT_NAME}"
		"include/AbstractGame.h"
		"src/AbstractGame.cpp"
		"include/GameEngine.h"
		"src/GameEngine.cpp"
		"resources/Resource.h"  
		"include/DataTypes.h" 
		"src/DataTypes.cpp" "include/LuaHandler.h")
		
# the include folder and resources has headers that will be shared to external project.
# the src folder also need to be included in case we have 
# headers for internal use.
target_include_directories("${PROJECT_NAME}"
		PUBLIC "./include"
		PUBLIC "./resources" 
		PRIVATE "./src" )

# fetch sol2 libraries
include(sol2_fetchcontent)

target_link_libraries("${PROJECT_NAME}"
		PUBLIC sol2::sol2 lua::lua )
