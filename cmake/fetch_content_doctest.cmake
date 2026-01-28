include(${CMAKE_CURRENT_LIST_DIR}/fetch_content.cmake)

set(DOCTEST_VERSION  "v2.4.12" CACHE STRING "doctest https://github.com/doctest/doctest.git")

set_fetch_content_dir(doctest)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        ${DOCTEST_VERSION}
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SUBBUILD_DIR   ${DOCTEST_FC_SUBBUILD_DIR}
  SOURCE_DIR     ${DOCTEST_FC_SOURCE_DIR}
  BINARY_DIR     ${DOCTEST_FC_BINARY_DIR}
  FIND_PACKAGE_ARGS NAMES doctest
)
unset_fetch_content_dir(doctest)

FetchContent_MakeAvailable(doctest)

include_directories(${doctest_SOURCE_DIR}/include)
