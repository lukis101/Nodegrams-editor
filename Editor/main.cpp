// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"

#include "Nodegrams/Nodegrams.h"
#include "Nodegrams/TypeRegistry.h"
#include "Nodegrams/nodes/NodeBase.h"
#include "Nodegrams/inoutlets/InletBase.h"
#include "Nodegrams/inoutlets/OutletBase.h"

#include "Nodegrams/nodes/time/SysTimeNode.h"
#include "Nodegrams/nodes/TestNode.h"
#include "Nodegrams/nodes/logic/gates/ANDGate.h"
#include "Nodegrams/nodes/logic/gates/ORGate.h"
#include "Nodegrams/nodes/logic/gates/XORGate.h"

#include "Nodegrams/datatypes/Event.h"
#include "Nodegrams/datatypes/Boolean.h"
#include "Nodegrams/datatypes/Float.h"
#include "Nodegrams/datatypes/Double.h"
#include "Nodegrams/datatypes/Int32.h"
#include "Nodegrams/datatypes/Int64.h"


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup Dss Engine
    //spdlog::set_level(spdlog::level::debug);
    auto l_ndgm = spdlog::stdout_logger_mt("Ndgm");
    //l_ndgm->set_level(spdlog::level::debug);
    auto l_ndgmdat = spdlog::stdout_logger_mt("Ndgm.data");
    //l_ndgmdat->set_level(spdlog::level::debug);
    auto l_iolet = spdlog::stdout_logger_mt("iolet");
    //l_iolet->set_level(spdlog::level::debug);

    Nodegrams::Nodegrams engine(l_ndgm);
    engine.Init();

    engine.typereg->RegisterDataType(new Nodegrams::Data::Event(&engine));
    engine.typereg->RegisterDataType(new Nodegrams::Data::Boolean(&engine));
    engine.typereg->RegisterDataType(new Nodegrams::Data::Float(&engine));
    engine.typereg->RegisterDataType(new Nodegrams::Data::Double(&engine));
    engine.typereg->RegisterDataType(new Nodegrams::Data::Int32(&engine));
    engine.typereg->RegisterDataType(new Nodegrams::Data::Int64(&engine));

    engine.RegisterNode(new Nodegrams::Nodes::SysTimeNode(&engine));
    engine.RegisterNode(new Nodegrams::Nodes::TestNode(&engine));
    engine.RegisterNode(new Nodegrams::Nodes::Logic::ANDGate(&engine));
    engine.RegisterNode(new Nodegrams::Nodes::Logic::ORGate(&engine));
    engine.RegisterNode(new Nodegrams::Nodes::Logic::XORGate(&engine));
    int tnode = engine.AddNode("TESTS:TestNode");
    int stnode = engine.AddNode("TIME:SysTimeNode");
    int andgatenode = engine.AddNode("LOGIC:GATES:AND gate");
    int orgatenode = engine.AddNode("LOGIC:GATES:OR gate");
    int xorgatenode = engine.AddNode("LOGIC:GATES:XOR gate");

    l_ndgm->info("PrintNodes: \n{}", engine.PrintNodes(true));

    l_ndgm->info("I-O connect 1 = {}", engine.ConnectInoutlets(stnode, 0, tnode, 1));
    l_ndgm->info("I-O connect 2 = {}", engine.ConnectInoutlets(stnode, 1, tnode, 0));

    auto l_gui = spdlog::stdout_logger_mt("GUI");

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "Unable to initialize GLFW\n");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Unable to create GLFW window\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Enable vsync

    if (!gladLoadGL())
    {
        fprintf(stderr, "Unable to initialize glad\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }



    // Setup ImGui binding
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    ImGui_ImplGlfwGL3_Init(window, true);

    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        engine.Update();

        ImGui_ImplGlfwGL3_NewFrame();

        // Node list window
        ImGui::Begin("Node list");
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            static int connids[4] = { 3, 1, 2, 1 };
            ImGui::InputInt4("node:iolet", connids);
            ImGui::SameLine();
            if (ImGui::Button("Connect"))
            {
                l_gui->info("Connecting iolets {}:{} -> {}:{}",
                    connids[0], connids[1], connids[2], connids[3]);
                engine.ConnectInoutlets(connids[0], connids[1], connids[2], connids[3]);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect"))
            {
                l_gui->info("Disconnecting iolets {}:{} -> {}:{}",
                    connids[0], connids[1], connids[2], connids[3]);
                engine.DisconnectInoutlets(connids[0], connids[1], connids[2], connids[3]);
            }

            // Registered Data Types
            if (ImGui::TreeNode("Data Types"))
            {
                for (auto& dt : engine.typereg->m_dtypes)
                {
                    ImGui::Text("[%d] %s", dt->GetTypeID(), dt->GetName().c_str());
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip(dt->GetDescription().c_str());
                }
                ImGui::TreePop();
            }

            // Registered Nodes
            if (ImGui::TreeNode("Available nodes"))
            {
                for (auto& node : engine.noderegistry)
                {
                    ImGui::Selectable(node.second->GetFullName().c_str());
                    if (ImGui::BeginPopupContextItem(node.second->GetFullName().c_str()))
                    {
                        if (ImGui::Selectable("Add"))
                            engine.AddNode(node.second->GetFullName());
                        if (ImGui::Selectable("Deregister"))
                            engine.DeregisterNode(node.second->GetFullName());
                        ImGui::EndPopup();
                    }
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip(node.second->GetDescription().c_str());
                }
                ImGui::TreePop();
            }

            // Current node graph
            if (ImGui::TreeNode("Node graph"))
            {
                for (auto& node : engine.m_nodes)
                {
                    char buffer [50];
                    int cx = snprintf(buffer, 50, "[%d] %s", node->GetID(), node->GetName().c_str());
                    if (ImGui::TreeNode(buffer))
                    {
                        if (ImGui::BeginPopupContextItem(buffer))
                        {
                            if (ImGui::Selectable("Remove"))
                            {
                                engine.RemoveNode(node->GetID());
                                ImGui::EndPopup();
                                ImGui::TreePop();
                                continue;
                            }
                            ImGui::EndPopup();
                        }

                        if (ImGui::IsItemHovered())
                            ImGui::SetTooltip(node->GetCategory().c_str());

                        // Inlets
                        int icnt = node->GetInletCount();
                        for (int i=0; i<icnt; i++)
                        {
                            auto inlet = node->GetInlet(i);
                            ImGui::Text("i (%u) %s : %s",
                                inlet->GetNumConnections(), inlet->name.c_str(), inlet->GetData()->GetName().c_str());
                            if (ImGui::BeginPopupContextItem(inlet->GetFullName().c_str()))
                            {
                                if (ImGui::Selectable("Connect"))
                                {
                                    connids[2] = node->GetID();
                                    connids[3] = i;
                                }
                                if (ImGui::Selectable("Disconnect all"))
                                    engine.ClearInletConnections(node->GetID(), i);
                                ImGui::EndPopup();
                            }
                            if (ImGui::IsItemHovered())
                            {
                                ImGui::BeginTooltip();
                                ImGui::Text(inlet->description.c_str());
                                ImGui::Text("%s = %s", inlet->GetData()->GetName().c_str(), inlet->GetDataString().c_str());
                                ImGui::EndTooltip();
                            }
                        }
                        // Outlets
                        int ocnt = node->GetOutletCount();
                        for (int i=0; i<ocnt; i++)
                        {
                            auto outlet = node->GetOutlet(i);
                            ImGui::Text("o (%u) %s : %s",
                                outlet->GetNumConnections(), outlet->name.c_str(), outlet->GetData()->GetName().c_str());
                            if (ImGui::BeginPopupContextItem(outlet->GetFullName().c_str()))
                            {
                                if (ImGui::Selectable("Connect"))
                                {
                                    connids[0] = node->GetID();
                                    connids[1] = i;
                                }
                                if (ImGui::Selectable("Disconnect all"))
                                    engine.ClearOutletConnections(node->GetID(), i);
                                ImGui::EndPopup();
                            }
                            if (ImGui::IsItemHovered())
                            {
                                ImGui::BeginTooltip();
                                ImGui::Text(outlet->description.c_str());
                                ImGui::Text("%s = %s", outlet->GetData()->GetName().c_str(), outlet->GetDataString().c_str());
                                ImGui::EndTooltip();
                            }
                        }
                        ImGui::TreePop();
                    }
                    else
                        if (ImGui::IsItemHovered())
                            ImGui::SetTooltip(node->GetCategory().c_str());
                }
                ImGui::TreePop();
            }

            ImGui::End();
        }

        // 1. Show a simple window.
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
        if (show_demo_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    engine.Shutdown();

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
