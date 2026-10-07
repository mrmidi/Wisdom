foreach(mode static shared headers)
  if(mode STREQUAL "static")
    set(wisdom_target wis::wisdom)
  elseif(mode STREQUAL "shared")
    set(wisdom_target wis::wisdom-shared)
  else()
    set(wisdom_target wis::wisdom-headers)
  endif()
  if(NOT TARGET ${wisdom_target})
    continue()
  endif()

  add_executable(metal-instance-cpp-${mode} instance_cpp.cpp)
  target_link_libraries(
    metal-instance-cpp-${mode} PRIVATE ${wisdom_target} Catch2::Catch2WithMain)
  set_target_properties(
    metal-instance-cpp-${mode}
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED YES
               CXX_EXTENSIONS NO)
  if(mode STREQUAL "headers")
    add_library(metal-instance-c-headers OBJECT headeronly_c.c)
    target_include_directories(
      metal-instance-c-headers
      PRIVATE "${WISDOM_METAL_API_DIR}/include"
              "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/include")
    target_compile_definitions(metal-instance-c-headers PRIVATE WISDOM_METAL=1)
    add_dependencies(metal-instance-c-headers generate-metal-api)
    set_target_properties(
      metal-instance-c-headers
      PROPERTIES C_STANDARD 11
                 C_STANDARD_REQUIRED YES
                 C_EXTENSIONS NO)
    target_sources(
      metal-instance-cpp-${mode}
      PRIVATE headeronly_peer.cpp $<TARGET_OBJECTS:metal-instance-c-headers>)
  else()
    add_executable(metal-instance-c-${mode} instance_c.c)
    target_link_libraries(metal-instance-c-${mode} PRIVATE ${wisdom_target})
    set_target_properties(
      metal-instance-c-${mode}
      PROPERTIES C_STANDARD 11
                 C_STANDARD_REQUIRED YES
                 C_EXTENSIONS NO
                 LINKER_LANGUAGE CXX)
    add_test(NAME metal-instance-c-${mode} COMMAND metal-instance-c-${mode})
    set_tests_properties(metal-instance-c-${mode} PROPERTIES TIMEOUT 10)
  endif()
  target_compile_options(
    metal-instance-cpp-${mode}
    PRIVATE -Wall -Wextra -Wunguarded-availability
            $<$<CONFIG:Debug>:-fno-omit-frame-pointer>)
  add_test(NAME metal-instance-cpp-${mode} COMMAND metal-instance-cpp-${mode})
  set_tests_properties(metal-instance-cpp-${mode} PROPERTIES TIMEOUT 10)
endforeach()
