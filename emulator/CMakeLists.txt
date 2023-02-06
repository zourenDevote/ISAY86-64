
project(emulator)

add_executable(${PROJECT_NAME}
        ins_emulator.h ins_emulator.cpp
        driver.cpp ../elf/myelf.h ../elf/myelf.cpp)

target_link_libraries(${PROJECT_NAME}
        error
        util
        assember
        parser)
