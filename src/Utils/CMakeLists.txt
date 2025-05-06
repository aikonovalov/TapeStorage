add_library(UtilsLib
    MemoryLayout.cpp
)

target_include_directories(UtilsLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)