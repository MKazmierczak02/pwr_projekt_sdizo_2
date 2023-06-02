cmake_minimum_required(VERSION 3.25)
project(projekt_sdizo_mk)

enable_testing()
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(SOURCE_FILES main.cpp)
add_executable(projekt_sdizo_2 ${SOURCE_FILES})

add_subdirectory(Structures)
add_subdirectory(tests)
add_subdirectory(Handlers)
