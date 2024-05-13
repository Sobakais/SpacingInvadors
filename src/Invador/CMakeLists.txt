add_library(invador invador.cpp invador.hpp)
target_include_directories(invador PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS invador)
