project(DecisionTreeTest)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/DecisionTree/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        DecisionTree
)

add_test(
    NAME DecisionTreeTest
    COMMAND ${PROJECT_NAME}
)