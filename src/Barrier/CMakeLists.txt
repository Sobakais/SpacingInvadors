add_library(barrier barrier.hpp barrier.cpp)
target_include_directories(barrier PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS barrier)
add_subdirectory(Block)
