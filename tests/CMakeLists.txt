
enable_testing()


file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.0.1/catch.hpp "${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp")

add_executable(tests catch.hpp test.cpp)
add_dependencies(tests dom)
target_include_directories(tests PUBLIC "../include")
target_link_libraries(tests dom)
