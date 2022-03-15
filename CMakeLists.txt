cmake_minimum_required(VERSION 3.10)
project(yellow_belt)

set(CMAKE_CXX_STANDARD 17)

add_executable(yellow_belt
        week-6/main.cpp
        week-6/database.cpp
        week-6/date.cpp
        week-6/node.cpp
        week-6/test_runner.cpp
        week-6/condition_parser.cpp
        week-6/condition_parser_test.cpp
        week-6/token.cpp
        week-6/unit_tests.cpp)
