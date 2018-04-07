
cmake_minimum_required(VERSION 3.6)

project(ImGui LANGUAGES CXX)

message(STATUS "Configuring ${PROJECT_NAME}")

set(_ImGui_Sources
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
)
set(_ImGui_Headers
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui_internal.h
    imgui/stb_rect_pack.h
    imgui/stb_textedit.h
    imgui/stb_truetype.h
)
source_group("${PROJECT_NAME}" FILES ${_ImGui_Sources} ${_ImGui_Headers})

add_library(${PROJECT_NAME} STATIC ${_ImGui_Sources} ${_ImGui_Headers})
# Create namespaced alias
add_library(ImGui::ImGui ALIAS ${PROJECT_NAME})

# Compiler requirements
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# Export library for downstream projects
export(TARGETS ${PROJECT_NAME} NAMESPACE ImGui:: FILE ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}/${PROJECT_NAME}-export.cmake)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${extlib_dir}/${PROJECT_NAME}")

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ImGuiTargets.cmake)
