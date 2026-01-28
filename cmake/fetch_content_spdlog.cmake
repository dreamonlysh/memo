include(${CMAKE_CURRENT_LIST_DIR}/fetch_content.cmake)

set(SPDLOG_VERSION "v1.14.1" CACHE STRING "spdlog tag(https://github.com/gabime/spdlog.git)")

set(SPDLOG_PATCH "diff --git a/include/spdlog/common.h b/include/spdlog/common.h
index aca483c2..952399ca 100644
--- a/include/spdlog/common.h
+++ b/include/spdlog/common.h
@@ -256,9 +256,9 @@ enum level_enum : int {
 #define SPDLOG_LEVEL_NAME_TRACE spdlog::string_view_t(\"trace\", 5)
 #define SPDLOG_LEVEL_NAME_DEBUG spdlog::string_view_t(\"debug\", 5)
 #define SPDLOG_LEVEL_NAME_INFO spdlog::string_view_t(\"info\", 4)
-#define SPDLOG_LEVEL_NAME_WARNING spdlog::string_view_t(\"warning\", 7)
+#define SPDLOG_LEVEL_NAME_WARNING spdlog::string_view_t(\"warn\", 4)
 #define SPDLOG_LEVEL_NAME_ERROR spdlog::string_view_t(\"error\", 5)
-#define SPDLOG_LEVEL_NAME_CRITICAL spdlog::string_view_t(\"critical\", 8)
+#define SPDLOG_LEVEL_NAME_CRITICAL spdlog::string_view_t(\"fatal\", 5)
 #define SPDLOG_LEVEL_NAME_OFF spdlog::string_view_t(\"off\", 3)

 #if !defined(SPDLOG_LEVEL_NAMES)
")

file(WRITE ${CMAKE_BINARY_DIR}/spdlog.patch "${SPDLOG_PATCH}")
set(SPDLOG_PATCH_COMMAND git apply "${CMAKE_BINARY_DIR}/spdlog.patch")

set_fetch_content_dir(spdlog)
FetchContent_Declare(
  spdlog
  # GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_REPOSITORY https://gitee.com/dreamonlyxl/spdlog-fork.git
  GIT_TAG ${SPDLOG_VERSION}
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  PATCH_COMMAND ${SPDLOG_PATCH_COMMAND}
  UPDATE_DISCONNECTED 1
  SUBBUILD_DIR ${SPDLOG_FC_SUBBUILD_DIR}
  SOURCE_DIR ${SPDLOG_FC_SOURCE_DIR}
  BINARY_DIR ${SPDLOG_FC_BINARY_DIR}
  FIND_PACKAGE_ARGS NAMES spdlog
)
unset_fetch_content_dir(spdlog)

FetchContent_MakeAvailable(spdlog)
