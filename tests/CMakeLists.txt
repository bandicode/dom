
enable_testing()

if(NOT DEFINED CACHE{DOM_BUILD_TESTS})
  set(DOM_BUILD_TESTS ON CACHE BOOL "whether to build dom library tests")
endif()

if(DOM_BUILD_TESTS)

  file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.0.1/catch.hpp "${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp")

  add_executable(TESTS_dom catch.hpp test.cpp)
  add_dependencies(TESTS_dom dom)
  target_include_directories(TESTS_dom PUBLIC "../include")
  target_link_libraries(TESTS_dom dom)

endif()
