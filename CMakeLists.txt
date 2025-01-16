cmake_minimum_required(VERSION 3.27)

project(
        SDOKU
        VERSION 1.0.0
        DESCRIPTION "SDOKU"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)

add_executable(main main.cpp)
target_include_directories(
        main PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(main PUBLIC sdoku)
