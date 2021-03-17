add_library(bitset bitset.c)
target_link_libraries(bitset PUBLIC bitset-h)
install(TARGETS bitset DESTINATION   ${CMAKE_INSTALL_LIBDIR}/cborg)