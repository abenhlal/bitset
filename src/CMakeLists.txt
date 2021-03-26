add_library(cborg-bitset bitset.c)
target_link_libraries(cborg-bitset PUBLIC cborg-bitset-h)
install(TARGETS cborg-bitset DESTINATION   ${CMAKE_INSTALL_LIBDIR}/cborg)