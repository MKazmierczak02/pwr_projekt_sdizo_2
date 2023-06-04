cmake_minimum_required(VERSION 3.25)
project(projekt_sdizo_mk)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
#set(CMAKE_EXE_LINKER_FLAGS "-static") # WON'T WORK ON MACOS
set(SOURCE_FILES main.cpp)
add_executable(projekt_sdizo_2 ${SOURCE_FILES})

add_subdirectory(Structures)
add_subdirectory(tests)
add_subdirectory(Handlers)
add_subdirectory(TimeTests)

file(COPY graf.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY graf2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY graf3.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})