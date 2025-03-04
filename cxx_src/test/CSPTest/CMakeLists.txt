project(CSPTest)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_SOURCE_DIR}/CSP/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        CSP
)

add_test(
    NAME CSPTest
    COMMAND ${PROJECT_NAME}
)