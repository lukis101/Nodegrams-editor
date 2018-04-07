
# CMake build configuration for Dreamshows

cmake_minimum_required(VERSION 3.6)

# enable folders in VS solutions
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Nodegrams-editor VERSION 0.1 LANGUAGES CXX)
message("${PROJECT_NAME} version: ${PROJECT_VERSION}")

# Parallel build in MSVC
if(MSVC_VERSION GREATER 1500)
    include(ProcessorCount)
    ProcessorCount(N)
    if(NOT N EQUAL 0)
    message("Using parallel build")
        SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /MP${N}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP${N}")
    endif()
endif()

include(GNUInstallDirs)
set(extlib_dir "external")

# Third-party librarires
add_subdirectory(external)
# Main parts
add_subdirectory(Nodegrams)
add_subdirectory(Editor)
