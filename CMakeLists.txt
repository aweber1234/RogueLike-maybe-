cmake_minimum_required(VERSION 3.31)

project(rogueLike LANGUAGES C)

add_executable(rogueLike main.c functions.c)

target_compile_definitions(rogueLike PRIVATE _XOPEN_SOURCE=700)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(rogueLike PRIVATE ncursesw)
