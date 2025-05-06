add_library(ConfigParserLib
    ConfigParser.cpp
)

target_include_directories(ConfigParserLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
