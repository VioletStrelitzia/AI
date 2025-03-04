project(Core)
# 生成核心库
file(GLOB CORE_SOURCES "src/*.cpp")
file(GLOB CORE_HEADERS "include/*.h")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} STATIC ${CORE_SOURCES})

# 包含目录
target_include_directories(Core
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)