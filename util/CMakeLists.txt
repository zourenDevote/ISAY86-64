
project(util)

add_library(${PROJECT_NAME} util.h util.cpp)

target_link_libraries(${PROJECT_NAME}
        error)