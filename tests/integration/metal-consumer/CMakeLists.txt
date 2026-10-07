cmake_minimum_required(VERSION 3.22)
project(metal-consumer LANGUAGES C CXX)

find_package(wisdom CONFIG REQUIRED)
include(CTest)

set(WISDOM_CONSUMER_MODES
    "static;shared;headers"
    CACHE STRING "Wisdom linkage modes required by the consumer tests")
if(NOT WISDOM_CONSUMER_MODES)
  message(FATAL_ERROR "Select at least one Wisdom consumer linkage mode")
endif()

foreach(mode ${WISDOM_CONSUMER_MODES})
  if(mode STREQUAL "static")
    set(wisdom_target wis::wisdom)
  elseif(mode STREQUAL "shared")
    set(wisdom_target wis::wisdom-shared)
  elseif(mode STREQUAL "headers")
    set(wisdom_target wis::wisdom-headers)
  else()
    message(FATAL_ERROR "Unknown Wisdom consumer linkage mode: ${mode}")
  endif()
  if(NOT TARGET ${wisdom_target})
    message(FATAL_ERROR "Required Wisdom consumer target is missing: ${wisdom_target}")
  endif()
  add_executable(metal-consumer-${mode} consumer.cpp)
  target_link_libraries(metal-consumer-${mode} PRIVATE ${wisdom_target})
  set_target_properties(
    metal-consumer-${mode}
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED YES
               CXX_EXTENSIONS NO
               C_STANDARD 11
               C_STANDARD_REQUIRED YES
               C_EXTENSIONS NO)
  if(mode STREQUAL "headers")
    target_sources(metal-consumer-${mode} PRIVATE headeronly_peer.cpp)
  else()
    target_sources(metal-consumer-${mode} PRIVATE consumer.c)
  endif()
  add_test(NAME metal-consumer-${mode} COMMAND metal-consumer-${mode})
  set_tests_properties(metal-consumer-${mode} PROPERTIES TIMEOUT 10)
endforeach()
