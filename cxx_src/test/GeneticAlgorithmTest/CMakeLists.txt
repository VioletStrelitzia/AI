project(GeneticAlgorithmTest)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/GeneticAlgorithm/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        GeneticAlgorithm
)

add_test(
    NAME GeneticAlgorithmTest
    COMMAND ${PROJECT_NAME}
)