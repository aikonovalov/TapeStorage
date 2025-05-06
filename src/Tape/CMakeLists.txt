add_library(TapeLib
    Tape.cpp
)

target_include_directories(TapeLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)