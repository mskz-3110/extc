include(${CMAKE_CURRENT_LIST_DIR}/common.cmake)

add_library(extc-shared SHARED ${EXTC_SRCS})
set_target_properties(extc-shared PROPERTIES OUTPUT_NAME extc)
add_library(extc-static STATIC ${EXTC_SRCS})
set_target_properties(extc-static PROPERTIES OUTPUT_NAME extc)
