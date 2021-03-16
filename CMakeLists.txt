cmake_minimum_required(VERSION 3.0)
project(bitset VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pedantic")

include(GNUInstallDirs)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(bitset src/bitset.c)

# install
install(TARGETS bitset ARCHIVE DESTINATION lib LIBRARY DESTINATION lib COMPONENT library)
install(FILES src/bitset.h DESTINATION  ${CMAKE_INSTALL_INCLUDEDIR})

# TEST
enable_testing()
add_executable(test_bitset tests/test_bitset.c)
add_test(test_bitset test_bitset)
target_link_libraries(test_bitset PUBLIC bitset)

# source: https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#can-i-do-make-uninstall-with-cmake
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
