include(FetchContent)

FetchContent_Declare(
    lua
    URL https://github.com/marovira/lua/archive/refs/tags/5.4.4.tar.gz
)
FetchContent_Declare(
    sol2
    URL https://github.com/ThePhD/sol2/archive/refs/tags/v3.3.0.tar.gz
)
FetchContent_MakeAvailable(lua)
FetchContent_MakeAvailable(sol2)
