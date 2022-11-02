cmake_minimum_required(VERSION 3.5)

project(thread CXX)

add_executable(
    threads
    topk_words.cpp
   )

add_executable(
    threads_init
    topk_words_init.cpp
   )

set_target_properties(
threads
PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()