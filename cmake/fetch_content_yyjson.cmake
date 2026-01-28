include(${CMAKE_CURRENT_LIST_DIR}/fetch_content.cmake)

set(YYJSON_VERSION  "0.9.0" CACHE STRING "yyjson tag(https://github.com/ibireme/yyjson.git)")

set_fetch_content_dir(yyjson)
FetchContent_Declare(
  yyjson
  # GIT_REPOSITORY https://github.com/ibireme/yyjson.git
  GIT_REPOSITORY https://gitee.com/dreamonlyxl/yyjson-fork.git
  GIT_TAG        ${YYJSON_VERSION}
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SUBBUILD_DIR   ${YYJSON_FC_SUBBUILD_DIR}
  SOURCE_DIR     ${YYJSON_FC_SOURCE_DIR}
  BINARY_DIR     ${YYJSON_FC_BINARY_DIR}
  FIND_PACKAGE_ARGS NAMES yyjson
)
unset_fetch_content_dir(yyjson)

FetchContent_MakeAvailable(yyjson)

add_library(yyjson::yyjson ALIAS yyjson)
