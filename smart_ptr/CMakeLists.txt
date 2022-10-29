cmake_minimum_required(VERSION 3.5)

project(container CXX)

find_package(GTest)

add_executable(
    containers_test
    test/list_tests.cpp
    test/listOR_tests.cpp
    test/successive_tests.cpp
    test/main_tests.cpp
)

target_include_directories(
    containers_test PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/list_container"
    "${CMAKE_CURRENT_SOURCE_DIR}/list_container_one_root"
    "${CMAKE_CURRENT_SOURCE_DIR}/successive_container"
)

target_include_directories(
    containers_test PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
    containers_test PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)
set_target_properties(
containers_test
PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()