add_executable(app
    main.cpp
    game_life.cpp
    Controller.cpp
)

find_package(Curses REQUIRED)

# include directories here
target_link_libraries(app PRIVATE
    utils
    automata
    math
    ${CURSES_LIBRARIES}
)

install(TARGETS app)
