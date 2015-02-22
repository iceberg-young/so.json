add_subdirectory(vendor/numeric/source)
add_dependencies(${PROJECT_NAME} so.numeric)
target_link_libraries(${PROJECT_NAME} so.numeric)

add_subdirectory(vendor/unicode/source)
add_dependencies(${PROJECT_NAME} so.unicode)
target_link_libraries(${PROJECT_NAME} so.unicode)
