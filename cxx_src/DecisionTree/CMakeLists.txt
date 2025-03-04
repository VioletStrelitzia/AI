project(DecisionTree)
file(GLOB DT_SOURCES "src/*.cpp")
file(GLOB DT_HEADERS "include/*.h")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CORE_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${DT_SOURCES})

target_include_directories(Core
    PUBLIC 
        ${CORE_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 链接核心库
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Core
)