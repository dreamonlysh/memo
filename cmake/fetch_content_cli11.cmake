include(${CMAKE_CURRENT_LIST_DIR}/fetch_content.cmake)

set(CLI11_VERSION  "v2.4.2" CACHE STRING "cli11 tag(https://github.com/CLIUtils/CLI11.git)")
set(CLI11_BUILD_TESTS OFF)
set(CLI11_BUILD_EXAMPLES OFF)

set_fetch_content_dir(cli11)
FetchContent_Declare(
  cli11
#  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_REPOSITORY https://gitee.com/dreamonlyxl/CLI11-fork.git
  GIT_TAG        ${CLI11_VERSION}
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SUBBUILD_DIR   ${CLI11_FC_SUBBUILD_DIR}
  SOURCE_DIR     ${CLI11_FC_SOURCE_DIR}
  BINARY_DIR     ${CLI11_FC_BINARY_DIR}
)
unset_fetch_content_dir(cli11)

FetchContent_MakeAvailable(cli11)

include_directories(${cli11_SOURCE_DIR}/include)
