add_subdirectory(Timer)
add_subdirectory(Parser)
add_subdirectory(Tape)
add_subdirectory(Utils)
add_subdirectory(Sorting)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    TimerLib
    ConfigParserLib
    UtilsLib
    SortingLib
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser
    ${CMAKE_CURRENT_SOURCE_DIR}/Tape
    ${CMAKE_CURRENT_SOURCE_DIR}/Sorting
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)  