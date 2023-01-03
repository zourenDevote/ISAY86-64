
project(emulatorDriver)

add_executable(${PROJECT_NAME} driver.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        ins_emulator
        util
        error
)