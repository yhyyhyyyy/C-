cmake_minimum_required(VERSION 3.10)
project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_MYMATH "Use MyMath implementation" ON)
configure_file(TutorialConfig.h.in TutorialConfig.h)

if(USE_MYMATH)
    add_subdirectory(MathFunctions)
endif()

add_executable(Tutorial tutorial.cpp)
target_include_directories(Tutorial PRIVATE "${PROJECT_BINARY_DIR}")

if(USE_MYMATH)
    target_link_libraries(Tutorial PRIVATE MathFunctions)
endif()
