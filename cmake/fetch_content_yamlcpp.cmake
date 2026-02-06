include(${CMAKE_CURRENT_LIST_DIR}/fetch_content.cmake)

set(YAMLCPP_VERSION  "yaml-cpp-0.9.0" CACHE STRING "yaml-cpp tag(https://github.com/jbeder/yaml-cpp.git)")
set(YAMLCPP_BUILD_TESTS OFF)
set(YAMLCPP_BUILD_EXAMPLES OFF)

set_fetch_content_dir(yamlcpp)
FetchContent_Declare(
  yamlcpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG        ${YAMLCPP_VERSION}
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
  SUBBUILD_DIR   ${YAMLCPP_FC_SUBBUILD_DIR}
  SOURCE_DIR     ${YAMLCPP_FC_SOURCE_DIR}
  BINARY_DIR     ${YAMLCPP_FC_BINARY_DIR}
)
unset_fetch_content_dir(yamlcpp)

FetchContent_MakeAvailable(yamlcpp)

include_directories(${yamlcpp_SOURCE_DIR}/include)
