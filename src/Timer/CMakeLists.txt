add_library(TimerLib
    Timer.cpp
)

target_include_directories(TimerLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)