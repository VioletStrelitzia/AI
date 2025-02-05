# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)

# 项目信息
project(AI VERSION 0.1.0 LANGUAGES C CXX)

#设置exe输出目录
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")

add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)

include_directories(inc)
include_directories(inc/NFigurePuzzle)
include_directories(inc/CSP)
include_directories(inc/DT)
include_directories(inc/DT/BDT)
include_directories(inc/ModelEvaluation)
include_directories(inc/NNSearch)
include_directories(inc/GA)
include_directories(inc/BN)
include_directories(inc/NN)
include_directories(inc/YUKII)
include_directories(test)

# 指定生成目标
aux_source_directory(src SOURCES)
aux_source_directory(src/YUKII SOURCES_YUKII)
aux_source_directory(src/NFigurePuzzle SOURCES_NFP)
aux_source_directory(src/CSP SOURCES_CSP)
aux_source_directory(src/DT SOURCES_DT)
aux_source_directory(src/DT/BDT SOURCES_BDT)
aux_source_directory(src/ModelEvaluation SOURCES_ME)
add_executable(AI ${SOURCES} ${SOURCES_YUKII} ${SOURCES_NFP} ${SOURCES_CSP} ${SOURCES_DT} ${SOURCES_BDT} ${SOURCES_ME})

if(0)
    message(STATUS "Build documentation open")
    include(cmake/build_doxygen.cmake)
    build_doxygen()
endif()
