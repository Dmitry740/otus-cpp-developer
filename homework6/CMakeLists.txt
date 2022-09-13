cmake_minimum_required(VERSION 3.5)

project(container CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(
	successive_container
	successive_container.cpp
)
add_executable(
	list_container
	list_container.cpp
)
add_executable(
	list_container_one_root
	list_container_one_root.cpp
)