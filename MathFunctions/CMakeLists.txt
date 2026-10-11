add_library(MathFunctions MathFunctions.cpp)

# Consumers inherit the header search path when linking this library.
target_include_directories(MathFunctions INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS MathFunctions
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(FILES MathFunctions.h DESTINATION include)
