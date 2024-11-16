# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

# 项目信息
project(AI VERSION 0.1.0 LANGUAGES C CXX)

#设置exe输出目录
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")

add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)

include_directories(inc)
include_directories(inc/NFigurePuzzle)
include_directories(inc/CSP)
include_directories(inc/DT)
include_directories(inc/utils)
include_directories(test)
 
# 指定生成目标
aux_source_directory(src SOURCES)
aux_source_directory(src/NFigurePuzzle SOURCES_NFP)
aux_source_directory(src/CSP SOURCES_CSP)
add_executable(AI ${SOURCES} ${SOURCES_NFP} ${SOURCES_CSP})
