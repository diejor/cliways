add_library(automata
    Gen.cpp
    Cell.cpp
)

target_link_libraries(automata PRIVATE
    utils
    math
)

target_include_directories(automata PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
