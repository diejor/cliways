add_library(math
    Loc.cpp
    Grid.cpp
)

target_link_libraries(math PUBLIC
    automata
)

target_include_directories(math PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
