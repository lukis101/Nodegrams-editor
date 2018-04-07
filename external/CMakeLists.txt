
#add_subdirectory(picojson)
#add_subdirectory(stb_image)

# ImGui configuration (until proper support is added)
#add_subdirectory(ThirdParty/imgui)
#find_package(ImGui CONFIG REQUIRED)
include(Lib_ImGui.cmake)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# GLAD
project(glad LANGUAGES C)
message(STATUS "Configuring ${PROJECT_NAME}")
add_library(${PROJECT_NAME} STATIC "glad/src/glad.c")
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC "glad/include")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${extlib_dir}/${PROJECT_NAME}")
