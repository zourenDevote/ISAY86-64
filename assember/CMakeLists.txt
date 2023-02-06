
project(assember)

add_library(${PROJECT_NAME} assember_support.h assember_support.cpp assember_checker.h assember_checker.cpp assember_ast.h assembly_ast_builder.h assembly_ast_builder.cpp assember_generate.h assember_generate.cpp assember.h)

target_link_libraries(${PROJECT_NAME} error util)

add_subdirectory(grammer)
