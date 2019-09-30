cmake_minimum_required(VERSION 3.10)

project(enum_visitor_test LANGUAGES CXX)

add_executable(enum_visitor_test
    test/main.cpp
)

target_include_directories(enum_visitor_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
