cmake_minimum_required(VERSION 3.28)
project(Spreadsheet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SPREADSHEET_SOURCES src/*.cpp)
file(GLOB_RECURSE SPREADSHEET_TEST_SOURCES test/*.cpp)
add_executable(spreadsheet
        ${SPREADSHEET_SOURCES}
        ${SPREADSHEET_TEST_SOURCES}
)

target_include_directories(spreadsheet PRIVATE
        ./include/core
        ./include/expressions
        ./test
)

if (MINGW)
    target_link_libraries(spreadsheet PRIVATE ${CMAKE_SOURCE_DIR}/lib/i686-w64-mingw32/libexpression_parser.a)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(spreadsheet PRIVATE ${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu/libexpression_parser.a)
elseif (APPLE)
    target_link_libraries(spreadsheet PRIVATE ${CMAKE_SOURCE_DIR}/lib/x86_64-darwin23-clang/libexpression_parser.a)
endif ()