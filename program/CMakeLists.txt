# Program CMakeList.txt, "Author": Manzini Alessandro
# Program specific logic here.
#
project("Program")

# create program target WIN32
add_executable(${PROJECT_NAME}
		WIN32
		"include/GameWinMain.h"
		"src/GameWinMain.cpp"
		"include/Game.h"
		"src/Game.cpp" )
		
# link library
target_link_libraries(${PROJECT_NAME}
		PRIVATE "GameEngine" )

# include program directories
target_include_directories(${PROJECT_NAME}
		PRIVATE "./include"
		PRIVATE "./src" )

# Set the source and destination directories for Lua scripts
set(REFRESH_SCRIPTS_COMMAND "RefreshLuaScripts")
set(SCRIPTS_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/scripts")
set(RESOURCES_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(SCRIPTS_DEST_FOLDER ${CMAKE_CURRENT_BINARY_DIR})

# Gather all Lua scripts in the source directory
file(GLOB MY_SCRIPTS "${SCRIPTS_FOLDER}/*.lua")

# Gather all resources in the source directory
file(GLOB_RECURSE MY_RESOURCES "${RESOURCES_FOLDER}/*")

# Define a custom command to copy Lua scripts
# This command depends on the Lua scripts in the source directory
add_custom_command( OUTPUT ${SCRIPTS_DEST_FOLDER}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MY_SCRIPTS} ${SCRIPTS_DEST_FOLDER} 
	COMMAND ${CMAKE_COMMAND} -E make_directory "${SCRIPTS_DEST_FOLDER}/resources"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MY_RESOURCES} "${SCRIPTS_DEST_FOLDER}/resources"
	DEPENDS ${MY_SCRIPTS} ${MY_RESOURCES}
	COMMENT "Refreshing scripts and resources ..." )

# Create a custom target that always checks Lua files
# ALL specifier makes sure it runs everytime if and only if the output of the custom command 
# is out of date with respect to its DEPENDS file(s)
add_custom_target(${REFRESH_SCRIPTS_COMMAND} ALL
    DEPENDS ${SCRIPTS_DEST_FOLDER} )

# Ensure your main project depends on the custom command
add_dependencies(${PROJECT_NAME} ${REFRESH_SCRIPTS_COMMAND})
