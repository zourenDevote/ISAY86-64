
project(elf)

FILE(GLOB SRC *.h *.cpp)

add_library(${PROJECT_NAME} ${SRC})

