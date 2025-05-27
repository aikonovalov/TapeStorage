add_library(TapeLib
    Tape.cpp
)

target_link_libraries(TapeLib PUBLIC
TimerLib)

target_include_directories(TapeLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)