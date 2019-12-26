
add_executable(EXAMPLE_html_paragraph html-paragraph.cpp)
add_dependencies(EXAMPLE_html_paragraph dom)
target_include_directories(EXAMPLE_html_paragraph PUBLIC "../include")
target_link_libraries(EXAMPLE_html_paragraph dom)
