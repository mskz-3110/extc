message("EXTC_CXX_FLAGS=${EXTC_CXX_FLAGS}")
message("EXTC_LIB_DIR=${EXTC_LIB_DIR}")
set(EXTC_PROJECT_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/..)
include_directories(${EXTC_PROJECT_ROOT_PATH}/inc)
set(EXTC_SRC_ROOT_PATH ${EXTC_PROJECT_ROOT_PATH}/src)

set(EXTC_SRCS)
list(APPEND EXTC_SRCS ${EXTC_SRC_ROOT_PATH}/extc.c)
list(APPEND EXTC_SRCS ${EXTC_SRC_ROOT_PATH}/extc/string.c)
