add_subdirectory(Spaceship)
add_subdirectory(Game)
add_subdirectory(Laser)
add_subdirectory(Barrier)

add_executable(main main.cpp)
target_link_libraries(main game spaceship laser barrier block sfml-graphics sfml-window sfml-system)
