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

# Step 4: install the executable and configured header.
install(TARGETS Tutorial RUNTIME DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# Step 4: run these tests with ctest --test-dir build -C Debug.
include(CTest)

if(BUILD_TESTING)
add_test(NAME DefaultInput COMMAND Tutorial)
set_tests_properties(DefaultInput PROPERTIES
    PASS_REGULAR_EXPRESSION "sqrt\\(9\\)=3")

function(check_sqrt name input expected)
    add_test(NAME ${name} COMMAND Tutorial ${input})
    set_tests_properties(${name} PROPERTIES
        PASS_REGULAR_EXPRESSION "sqrt\\(${input}\\)=${expected}")
endfunction()

check_sqrt(Square4 4 "2")
check_sqrt(Square9 9 "3")
check_sqrt(Square25 25 "5")
check_sqrt(FractionalResult 5 "2\\.23607")
check_sqrt(Zero 0 "0")
check_sqrt(SmallNumber 0.0001 "0\\.01")
check_sqrt(LargeNumber 10000 "100")

add_test(NAME InvalidText COMMAND Tutorial abc)
add_test(NAME TrailingText COMMAND Tutorial 9abc)
add_test(NAME NonFinite COMMAND Tutorial nan)
add_test(NAME TooManyArguments COMMAND Tutorial 9 16)
set_tests_properties(InvalidText TrailingText NonFinite TooManyArguments
    PROPERTIES WILL_FAIL TRUE)


endif()

# Step 7: portable ZIP binary and source distributions.
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Tutorial")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CMake tutorial square-root calculator")
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/[.]git/;/[.]vscode/;[.]exe$;[.]obj$;[.]lib$")
include(CPack)

