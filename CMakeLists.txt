cmake_minimum_required(VERSION 4.1.2)
project(application CXX)



add_executable(application src/application.cpp src/main.cpp)



install(TARGETS application DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
