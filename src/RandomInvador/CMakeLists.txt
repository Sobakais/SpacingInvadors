add_library(randinv randominvador.cpp randominvador.hpp)
target_include_directories(randinv PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS randinv)
