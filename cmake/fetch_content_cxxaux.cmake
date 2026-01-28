include(${CMAKE_CURRENT_LIST_DIR}/fetch_content.cmake)

set(CXX_AUX_VERSION  "HEAD" CACHE STRING "cxx-aux https://gitee.com/dreamonlyxl/cxx-aux.git")

set_fetch_content_dir(cxxaux)
FetchContent_Declare(
  cxxaux
  GIT_REPOSITORY https://gitee.com/dreamonlyxl/cxx-aux.git
  GIT_TAG        ${CXXAUX_VERSION}
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SUBBUILD_DIR   ${CXXAUX_FC_SUBBUILD_DIR}
  SOURCE_DIR     ${CXXAUX_FC_SOURCE_DIR}
  BINARY_DIR     ${CXXAUX_FC_BINARY_DIR}
  FIND_PACKAGE_ARGS NAMES cxxaux
)
unset_fetch_content_dir(cxxaux)

FetchContent_MakeAvailable(cxxaux)

include_directories(${cxxaux_SOURCE_DIR}/include)
