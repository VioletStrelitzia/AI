project(NFigurePuzzleTest)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/NFigurePuzzle/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        NFigurePuzzle
)

add_test(
    NAME NFigurePuzzleTest
    COMMAND ${PROJECT_NAME}
)