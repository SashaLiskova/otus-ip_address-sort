
add_library(utils Parser.cpp)

target_include_directories(utils PRIVATE "${CMAKE_SOURCE_DIR}/ipv4")
target_link_libraries(utils PRIVATE ipv4)
