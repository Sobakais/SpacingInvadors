add_library(spaceship spaceship.cpp spaceship.hpp)
target_include_directories(spaceship PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS spaceship)
