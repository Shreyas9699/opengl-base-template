#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <algorithm>

#include "Shapes.h"

int windowWidth = 1440;
int windowHeight = 800;

CameraSettings cam;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            cam.isDragging = true;
            glfwGetCursorPos(window, &cam.lastX, &cam.lastY);
        }
        else if (action == GLFW_RELEASE)
        {
            cam.isDragging = false;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.zoom += yoffset * 0.1f;
    cam.zoom = std::max(0.1f, std::min(cam.zoom, 5.0f));
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Rendering Window", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glewInit();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LIGHTING);

    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // Setup ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Enable ImGui docking and multi-viewport features
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Variables to store the current shape to draw
    enum Shape { NONE, CIRCLE, TRIANGLE, RECTANGLE, SQUARE };
    Shape currentShape = NONE;
    ImVec4 tempColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    Shapes obj(tempColor, false);


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create ImGui windows
        ImGui::Begin("Shape Selector");
        if (ImGui::Button("Circle")) currentShape = CIRCLE;
        if (ImGui::Button("Triangle")) currentShape = TRIANGLE;
        if (ImGui::Button("Rectangle")) currentShape = RECTANGLE;
        if (ImGui::Button("Square")) currentShape = SQUARE;
        ImGui::ColorEdit3("Shape Color", (float*)&tempColor);
        obj.color = tempColor;
        ImGui::Checkbox("3D Mode", &obj.is3D);
        ImGui::End();

        ImGui::Begin("Controls");
        ImGui::SliderFloat("Zoom", &cam.zoom, 0.1f, 5.0f);
        ImGui::SliderFloat("Rotation X", &cam.rotationX, -360.0f, 360.0f);
        ImGui::SliderFloat("Rotation Y", &cam.rotationY, -360.0f, 360.0f);
        if (ImGui::Button("Reset")) { cam.reset(); }
        ImGui::End();

        // Handle mouse dragging for rotation
        if (cam.isDragging)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            double dx = xpos - cam.lastX;
            double dy = ypos - cam.lastY;
            cam.rotationY += dx * 0.5f;
            cam.rotationX += dy * 0.5f;
            cam.lastX = xpos;
            cam.lastY = ypos;
        }

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up perspective projection with GLM
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));

        // Draw the selected shape
        switch (currentShape)
        {
        case CIRCLE:
            obj.drawCircle(cam);
            break;
        case TRIANGLE:
            obj.drawTriangle(cam);
            break;
        case RECTANGLE:
            obj.drawRect(cam);
            break;
        case SQUARE:
            obj.drawSquare(cam);
            break;
        default:
            break;
        }

        // ImGui rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and render additional ImGui windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}