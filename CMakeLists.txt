
# CMake build configuration for Dreamshows

cmake_minimum_required(VERSION 3.6)

# enable folders in VS solutions
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Nodegrams-editor VERSION 0.1 LANGUAGES CXX)
message("${PROJECT_NAME} version: ${PROJECT_VERSION}")

include(GNUInstallDirs)
set(extlib_dir "external")

# Third-party librarires
add_subdirectory(external)
# Main parts
add_subdirectory(Nodegrams)
add_subdirectory(Editor)
