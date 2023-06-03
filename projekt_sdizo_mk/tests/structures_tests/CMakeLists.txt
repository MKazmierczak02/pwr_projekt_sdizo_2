include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runStructuresTests
        GraphListTests.cpp GraphMatrixTests.cpp)

target_link_libraries(runStructuresTests gtest gtest_main)

add_subdirectory(testfiles)

file(COPY testfiles/graf.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY testfiles/graf2.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY testfiles/graf3.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})