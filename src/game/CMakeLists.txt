add_executable(app
    main.cpp
    game_life.cpp
)

# include directories here
target_link_libraries(app PRIVATE
    utils
    automata
    math
)

install(TARGETS app)
