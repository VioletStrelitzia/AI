project(CoreTest)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Core/include)

target_link_libraries(${PROJECT_NAME} PUBLIC Core)

add_test(
    NAME CoreTest
    COMMAND ${PROJECT_NAME}
)