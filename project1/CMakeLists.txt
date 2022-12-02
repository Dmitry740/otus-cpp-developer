cmake_minimum_required(VERSION 3.10.2)

project(Rent_Car CXX)

add_executable(rent_car rent_car.cpp db.cpp)
    
set(Boost_USE_MULTITHREADED ON)
   
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
include_directories(${CURL_INCLUDE_DIRS})
add_definitions(-DHAVE_CURL)
endif()
    
add_executable(bot chat_bot.cpp main.cpp db.cpp)
    
target_link_libraries(bot PRIVATE C:/src/vcpkg/vcpkg/installed/x64-windows/lib/TgBot.lib ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

add_executable(tests test.cpp db.cpp)
    
find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)


find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(rent_car PRIVATE unofficial::sqlite3::sqlite3)

set_target_properties(
rent_car
PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4 /WX)
    else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()