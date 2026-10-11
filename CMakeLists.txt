cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)


option(USE_MYMATH "Use MyMath implementation" ON)


if(USE_MYMATH)
    add_subdirectory(MathFunctions)
endif()


add_executable(Tutorial tutorial.cpp)


if(USE_MYMATH)
    target_link_libraries(Tutorial MathFunctions)
endif()


target_include_directories(Tutorial PUBLIC
    "${PROJECT_SOURCE_DIR}/MathFunctions"
)