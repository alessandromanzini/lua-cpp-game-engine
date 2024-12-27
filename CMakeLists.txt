# Master CMakeList.txt : CMake project for LuaBindingsGameEngine, Manzini Alessandro
# Project specific logic here.
#
cmake_minimum_required (VERSION 3.24.1)

# set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure C++20 is strictly required
message(STATUS "C++20 support has been enabled by default.")

# set the project name
project(LuaBindingsGameEngine)

# set unicode
add_compile_definitions(PUBLIC UNICODE
		PUBLIC _UNICODE)

# enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# add /bigobj to the compiler flags for MSVC
if(MSVC)
    add_compile_options(/bigobj)
endif()

# append cmake module path
# making sure cmake finds our custom modules (.cmake)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Add subdirectories
add_subdirectory("engine")
add_subdirectory("program")
