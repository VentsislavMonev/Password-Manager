cmake_minimum_required(VERSION 3.10)
project(Password_Manager VERSION 0.1.0 LANGUAGES C CXX)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCE_FILES
    main.cpp
    cpp/*.cpp
)

# Create the executable
add_executable(Password_Manager ${SOURCE_FILES})

# Include headers from the hpp folder
target_include_directories(Password_Manager PRIVATE hpp)
