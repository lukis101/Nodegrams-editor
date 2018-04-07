

find_package(OpenGL REQUIRED)
#find_package(ImGui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    imgui_impl_glfw_gl3.h
    imgui_impl_glfw_gl3.cpp
    main.cpp
)

target_include_directories(${PROJECT_NAME} INTERFACE ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ImGui
        ${OPENGL_LIBRARIES}
        glad
        glfw
        spdlog::spdlog
        Nodegrams::Nodegrams
)
