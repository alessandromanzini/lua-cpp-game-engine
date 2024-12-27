# lua-cpp-game-engine
I'm going to give a quick overview of how I ported the engine in Lua.

## CMake
I'm using CMake to setup the project and configure the build. The structure is the following:
There's the master CMakeLists.txt file in the root directory, which sets the project specifics and includes the subdirectories engine and program. 

The engine directory contains the source code of the engine and it fetches the sol library. 

The program directory contains the game interface, that will interact directly with lua using the binding.
The program also copies the lua scripts and the resources to the build directory. Since we ideally won't be rebuilding the source code,
I implemented a custom command to copy everything and appended it as a dependency to the program target.
This way, the resources and scripts will be copied every time they've been changed when the program is executed, without needing a rebuild.

To specify which files to track I use the file(GLOB_RECURSE) command, which will fetch all the files in the specified directory and its subdirectories.
Since globbing doesn't update on its own, I added a custom error message for missing files, so the user will remember to delete the cache and  
reconfigure in case any file is missing.

## Binding
The binding is done using the sol library, for which I created a couple of handy tools to make the binding easier. For starters, I created a wrapper 
class for the sol::state, which will provide handy functions to access data safely. 
SafeInvoke will call a function and catch any errors that might occur, calling my custom error handler.
The handler - which is also called by the lua scripts in case of errors - will display a message box to the screen with the error message and the line where it occurred.

To instantiate the wrapper I use another custom class, the LuaLoader, which will load the lua scripts and bind the engine functions. The LuaLoader will
populate a wrapper instance, but it can also create a vanilla sol::state instance, in case the user wants to use it directly.
The interesting part about the LuaLoader is that the LoadScript method is templated and accepts a functor type that will contain the binding logic for the
engine. By default it will use the DefaultLuaBinder class, containing all the binding logic that I implemented. Should a user want to add more bindings,
they can create a new class (possibly inheriting from the default binder) and pass it as a template argument to the LoadScript method.

Finally, in the initialize game hook I create a LuaHandler wrapper and link the active GAME_ENGINE instance as well as some Game functions to provide the Lua script
with the tools to make a game.
The rest of the game class only serves as a bridge between the engine and the Lua scripts, calling the LuaHandler methods during all the steps of the
game lifecycle (start, paint, tick, ...).

## Lua
I carefully typed all the user_types annotations to provide a comprehensive documentation for the scripting.
I also created a couple of sample scripts to demonstrate some of the ported features.

To facilitate development, I created a file_utils module that will aid in loading resources while also checking for their existence.
