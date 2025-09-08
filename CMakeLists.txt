cmake_minimum_required(VERSION 3.22.1) # current version on my ubuntu

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version") 
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION}) 


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -pedantic
    -Werror
)

option(WITH_GTEST_TEST "Whether to build GTest test" ON)

add_subdirectory(ipv4)
add_subdirectory(utils)


add_executable(ip_filter main.cpp)

target_include_directories(ip_filter PRIVATE 
      "${CMAKE_SOURCE_DIR}/utils"
      "${CMAKE_SOURCE_DIR}/ipv4"
)
target_link_libraries(ip_filter PRIVATE ipv4 utils)




if(WITH_GTEST_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()
           

install(TARGETS ip_filter RUNTIME DESTINATION bin)
#creste debian package
set(CPACK_GENERATOR DEB)
#sets the veriosn of package
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandrabrsk7ls@gmail.com)
include(CPack)

#command make --build . --target package will create .deb package 


