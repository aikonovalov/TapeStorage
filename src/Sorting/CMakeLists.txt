add_library(SortingLib
    Sorting.cpp
)
target_link_libraries(SortingLib PUBLIC
TapeLib
UtilsLib)

target_include_directories(SortingLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)