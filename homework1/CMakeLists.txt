cmake_minimum_required(VERSION 3.8)

project(hello CXX)

add_executable(hello example.cpp move_me_out.cpp hello_world.cpp)

target_compile_features(hello PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(hello PUBLIC /W4 /WX)
else()
    target_compile_options(hello PUBLIC -Wall -Wextra -Werror -pedantic)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_compile_options(statistics PRIVATE
-g
-Wall
-Wextra
-Werror
-pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
target_compile_options(statistics PRIVATE
/EHsc
/W4
/WX)
endif()