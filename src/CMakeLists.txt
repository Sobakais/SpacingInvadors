add_subdirectory(Spaceship)
add_subdirectory(Game)
add_subdirectory(Laser)

add_executable(main main.cpp)
target_link_libraries(main game spaceship laser sfml-graphics sfml-window sfml-system)
