cmake_minimum_required(VERSION 4.1.2)
project(application CXX)



add_executable(application src/main.cpp)
target_compile_features(application PUBLIC cxx_std_23)