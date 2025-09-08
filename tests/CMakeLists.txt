include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(test_ipv4 Ipv4Test.cpp)
target_include_directories(test_ipv4 PRIVATE "${CMAKE_SOURCE_DIR}/ipv4")

target_link_libraries(test_ipv4
  GTest::gtest_main
  ipv4
)

add_executable(test_parser ParserTest.cpp)
target_include_directories(test_parser PRIVATE 
      "${CMAKE_SOURCE_DIR}/utils"
      "${CMAKE_SOURCE_DIR}/ipv4"
)

target_link_libraries(test_parser
  GTest::gtest_main
  ipv4
  utils
)

include(GoogleTest)
gtest_discover_tests(test_ipv4)
gtest_discover_tests(test_parser)

# Make sure they are built when you build the project
add_custom_target(tests ALL
    DEPENDS test_ipv4 test_parser 
)
