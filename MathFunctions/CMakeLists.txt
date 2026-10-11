add_library(MathFunctions MathFunctions.cpp)

# Consumers inherit the header search path when linking this library.
target_include_directories(MathFunctions INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
