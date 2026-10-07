set(WISDOM_METAL_CPP_PATH "" CACHE PATH "Path to installed metal-cpp headers")

if (NOT WISDOM_METAL_CPP_PATH)
    find_path(METAL_CPP_INSTALLED_PATH Metal/Metal.hpp)
endif ()

if (WISDOM_METAL_CPP_PATH)
    set(METAL_CPP_INCLUDE_DIR "${WISDOM_METAL_CPP_PATH}")
elseif (METAL_CPP_INSTALLED_PATH)
    set(METAL_CPP_INCLUDE_DIR "${METAL_CPP_INSTALLED_PATH}")
else ()
    CPMAddPackage(
            NAME metal_cpp
            URL https://codeload.github.com/apple/metal-cpp/tar.gz/f567ed836e4cbb85788c42115a2682bbe68097ee
            URL_HASH SHA256=c3d867f795340934ce3d61b06f84bd019528102fb8ea45e0f193d6ae24912e62
            DOWNLOAD_ONLY TRUE)
    set(METAL_CPP_INCLUDE_DIR "${metal_cpp_SOURCE_DIR}")
endif ()

foreach(header Metal/Metal.hpp Metal/MTL4CommandQueue.hpp Metal/MTL4CommandAllocator.hpp)
    if (NOT EXISTS "${METAL_CPP_INCLUDE_DIR}/${header}")
        message(FATAL_ERROR "Metal 4 binding header missing: ${METAL_CPP_INCLUDE_DIR}/${header}")
    endif ()
endforeach()

# Install the Metal 4 bindings with Wisdom so consumers do not need CPM.
install(DIRECTORY "${METAL_CPP_INCLUDE_DIR}/Foundation"
                  "${METAL_CPP_INCLUDE_DIR}/Metal"
                  "${METAL_CPP_INCLUDE_DIR}/QuartzCore"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/wisdom/metal-cpp)
install(FILES "${METAL_CPP_INCLUDE_DIR}/LICENSE.txt"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/wisdom/metal-cpp OPTIONAL)
