add_subdirectory(vendor/text/source)
add_dependencies(${PROJECT_NAME} so.text)
target_link_libraries(${PROJECT_NAME} so.text)
