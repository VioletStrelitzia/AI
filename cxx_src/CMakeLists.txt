project(cxx_src)

set(CORE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/core/include)

add_subdirectory(Core)
add_subdirectory(DecisionTree)
add_subdirectory(CSP)
add_subdirectory(NFigurePuzzle)
add_subdirectory(GeneticAlgorithm)
add_subdirectory(test)