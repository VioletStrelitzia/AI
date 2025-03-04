cmake_minimum_required(VERSION 3.10.0)

project(AI
    VERSION 0.1.0
    DESCRIPTION "Learn to make an AI!"
    HOMEPAGE_URL "https://github.com/VioletStrelitzia/AI"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)  # 动态库路径

add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)

enable_testing()
add_subdirectory(cxx_src)

if(0)
    message(STATUS "Build documentation open")
    include(cmake/build_doxygen.cmake)
    build_doxygen()
endif()