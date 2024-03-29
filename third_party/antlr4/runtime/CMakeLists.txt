option(ANTLR_BUILD_CPP_TESTS "Build C++ tests." OFF)

include_directories(
  ${PROJECT_SOURCE_DIR}/runtime/src
  ${PROJECT_SOURCE_DIR}/runtime/src/atn
  ${PROJECT_SOURCE_DIR}/runtime/src/dfa
  ${PROJECT_SOURCE_DIR}/runtime/src/internal
  ${PROJECT_SOURCE_DIR}/runtime/src/misc
  ${PROJECT_SOURCE_DIR}/runtime/src/support
  ${PROJECT_SOURCE_DIR}/runtime/src/tree
  ${PROJECT_SOURCE_DIR}/runtime/src/tree/pattern
  ${PROJECT_SOURCE_DIR}/runtime/src/tree/xpath
)


file(GLOB libantlrcpp_SRC
  "${PROJECT_SOURCE_DIR}/runtime/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/atn/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/dfa/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/internal/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/misc/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/support/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/tree/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/tree/pattern/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/tree/xpath/*.cpp"
)

add_library(antlr4_shared SHARED ${libantlrcpp_SRC})
add_library(antlr4_static STATIC ${libantlrcpp_SRC})

# Make sure to link against threads (pthreads) library in order to be able to
# make use of std::call_once in the code without producing runtime errors
# (see also https://github.com/antlr/antlr4/issues/3708 and/or https://stackoverflow.com/q/51584960).
find_package(Threads REQUIRED)
target_link_libraries(antlr4_shared Threads::Threads)
target_link_libraries(antlr4_static Threads::Threads)

if (ANTLR_BUILD_CPP_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
  )

  if(WITH_STATIC_CRT)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  endif()

  FetchContent_MakeAvailable(googletest)

  file(GLOB libantlrcpp_TESTS
    "${PROJECT_SOURCE_DIR}/runtime/tests/*.cpp"
  )

  add_executable(
    antlr4_tests
    ${libantlrcpp_TESTS}
  )

  target_link_libraries(
    antlr4_tests
    antlr4_static
    gtest_main
  )

  include(GoogleTest)

  gtest_discover_tests(antlr4_tests)
endif()

if(APPLE)
  target_link_libraries(antlr4_shared ${COREFOUNDATION_LIBRARY})
  target_link_libraries(antlr4_static ${COREFOUNDATION_LIBRARY})
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(disabled_compile_warnings "/wd4251")
else()
  set(disabled_compile_warnings "-Wno-overloaded-virtual")
endif()


if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(disabled_compile_warnings "${disabled_compile_warnings} -Wno-dollar-in-identifier-extension -Wno-four-char-constants")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  set(disabled_compile_warnings "${disabled_compile_warnings} -Wno-multichar")
endif()

set(extra_share_compile_flags "")
set(extra_static_compile_flags "")
set(static_lib_suffix "")

if (WIN32)
  set(static_lib_suffix "-static")
  target_compile_definitions(antlr4_shared PUBLIC ANTLR4CPP_EXPORTS)
  target_compile_definitions(antlr4_static PUBLIC ANTLR4CPP_STATIC)
  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(extra_share_compile_flags "-MP /wd4251")
    set(extra_static_compile_flags "-MP")
  endif()
endif()

set_target_properties(antlr4_shared
                      PROPERTIES VERSION   ${ANTLR_VERSION}
                                 SOVERSION ${ANTLR_VERSION}
                                 OUTPUT_NAME antlr4-runtime
                                 COMPILE_FLAGS "${disabled_compile_warnings} ${extra_share_compile_flags}")

set_target_properties(antlr4_static
                      PROPERTIES VERSION   ${ANTLR_VERSION}
                                 SOVERSION ${ANTLR_VERSION}
                                 OUTPUT_NAME "antlr4-runtime${static_lib_suffix}"
                                 COMPILE_PDB_NAME "antlr4-runtime${static_lib_suffix}"
                                 COMPILE_FLAGS "${disabled_compile_warnings} ${extra_static_compile_flags}")

if (ANTLR_BUILD_CPP_TESTS)
  # Copy the generated binaries to dist folder (required by test suite)
  add_custom_command(
    TARGET antlr4_shared
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_HOME_DIRECTORY}/dist
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:antlr4_shared> ${CMAKE_HOME_DIRECTORY}/dist
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_LINKER_FILE:antlr4_shared> ${CMAKE_HOME_DIRECTORY}/dist)
  
  add_custom_command(
    TARGET antlr4_static
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_HOME_DIRECTORY}/dist
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:antlr4_static> ${CMAKE_HOME_DIRECTORY}/dist)
endif()

install(TARGETS antlr4_shared
        EXPORT antlr4-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(TARGETS antlr4_static
        EXPORT antlr4-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY "${PROJECT_SOURCE_DIR}/runtime/src/"
        DESTINATION "include/antlr4-runtime"
        COMPONENT dev
        FILES_MATCHING PATTERN "*.h"
        )
