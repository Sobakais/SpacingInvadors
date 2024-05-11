add_subdirectory(Spaceship)
add_subdirectory(Game)

add_executable(main main.cpp)
target_link_libraries(main game spaceship sfml-graphics sfml-window sfml-system)

