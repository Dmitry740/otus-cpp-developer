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
	main_successive
	successive_container/main_successive.cpp
)
add_executable(
	main_list
	list_container/main_list.cpp
)
add_executable(
	main_list_one_root
	list_container_one_root/main_list_one_root.cpp
)