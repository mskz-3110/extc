include(${CMAKE_CURRENT_LIST_DIR}/lib.cmake)

link_directories(${EXTC_LIB_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTC_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
set(EXTC_TESTS_ROOT_PATH ${EXTC_PROJECT_ROOT_PATH}/tests)
include_directories(${EXTC_TESTS_ROOT_PATH})

set(EXTC_TEST_NAMES)
list(APPEND EXTC_TEST_NAMES test_string)

foreach(testName IN LISTS EXTC_TEST_NAMES)
  add_executable(${testName} ${EXTC_TESTS_ROOT_PATH}/${testName}.cpp)
  target_link_libraries(${testName} extc-static)
endforeach()
