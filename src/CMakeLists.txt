include(${CMAKE_SOURCE_DIR}/cmake/fetch_content_cli11.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/fetch_content_yamlcpp.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} config_loader.cpp executor.cpp memo.cpp)

target_link_libraries(${PROJECT_NAME} yaml-cpp::yaml-cpp)
