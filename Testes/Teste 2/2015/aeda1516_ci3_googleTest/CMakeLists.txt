cmake_minimum_required(VERSION 3.10)
project(aeda1516_ci3)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(aeda1516_ci3 main.cpp Tests/Test.cpp Tests/Dish.h Tests/Restaurant.h Tests/Dish.cpp Tests/Restaurant.cpp Tests/Table.h Tests/Table.cpp)

target_link_libraries(aeda1516_ci3 gtest gtest_main)
