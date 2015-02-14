add_subdirectory(vendor/numeric/source)
add_dependencies(${PROJECT_NAME} so.numeric)
target_link_libraries(${PROJECT_NAME} so.numeric)
