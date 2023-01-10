
project(parser)


add_library(${PROJECT_NAME}
        ParserParser.h ParserLexer.h ParserListener.h ParserBaseListener.h
        ParserBaseVisitor.h ParserVisitor.h
        ParserParser.cpp ParserLexer.cpp ParserListener.cpp ParserBaseListener.cpp
        ParserBaseVisitor.cpp ParserVisitor.cpp ../assember_ast.cpp)

target_link_libraries(${PROJECT_NAME} antlr4-runtime)

