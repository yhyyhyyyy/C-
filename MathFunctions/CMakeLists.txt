add_library(MathFunctions MathFunctions.cpp)

# Consumers inherit the header search path when linking this library.
target_include_directories(MathFunctions INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS MathFunctions
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(FILES MathFunctions.h DESTINATION include)

# Step 5: detect functions before using platform-dependent code.
include(CheckCXXSymbolExists)
check_cxx_symbol_exists(log "math.h" HAVE_LOG)
check_cxx_symbol_exists(exp "math.h" HAVE_EXP)
if(HAVE_LOG AND HAVE_EXP)
    target_compile_definitions(MathFunctions PRIVATE HAVE_LOG HAVE_EXP)
endif()

