# Step 6: build a generator, then generate a header before compiling the library.
add_executable(MakeTable MakeTable.cpp)
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Table.h"
    COMMAND MakeTable "${CMAKE_CURRENT_BINARY_DIR}/Table.h"
    DEPENDS MakeTable
    COMMENT "Generating square-root lookup table"
    VERBATIM)

add_library(MathFunctions MathFunctions.cpp "${CMAKE_CURRENT_BINARY_DIR}/Table.h")
target_include_directories(MathFunctions
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

install(TARGETS MathFunctions
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(FILES MathFunctions.h DESTINATION include)
