
project(assember)

add_library(${PROJECT_NAME} assember_support.h assember_support.cpp assember_parser.h assember_parser.cpp assember_ast.h assembly_ast_builder.h assembly_ast_builder.cpp)

target_link_libraries(${PROJECT_NAME} error util)

add_subdirectory(grammer)
