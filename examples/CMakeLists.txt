
if(NOT DEFINED CACHE{DOM_BUILD_EXAMPLES})
  set(DOM_BUILD_EXAMPLES ON CACHE BOOL "whether to build dom library examples")
endif()

if(DOM_BUILD_EXAMPLES)

  add_executable(EXAMPLE_html_paragraph html-paragraph.cpp)
  add_dependencies(EXAMPLE_html_paragraph dom)
  target_include_directories(EXAMPLE_html_paragraph PUBLIC "../include")
  target_link_libraries(EXAMPLE_html_paragraph dom)

endif()
