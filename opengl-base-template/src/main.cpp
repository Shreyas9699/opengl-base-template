#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <algorithm>

#include "Shapes.h"

int windowWidth = 1280;
int windowHeight = 900;

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

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // You can use GL_LIGHT1, GL_LIGHT2, etc., for multiple lights

    // Set light source properties
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // Directional light from the top right
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

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
    Shapes obj(false);

    // Variables for light properties
    ImVec4 lightAmbient = ImVec4(light_ambient[0], light_ambient[1], light_ambient[2], light_ambient[3]);
    ImVec4 lightDiffuse = ImVec4(light_diffuse[0], light_diffuse[1], light_diffuse[2], light_diffuse[3]);
    ImVec4 lightSpecular = ImVec4(light_specular[0], light_specular[1], light_specular[2], light_specular[3]);

    MaterialProperty mat_prop;

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
        ImGui::Checkbox("3D Mode", &obj.is3D);
        ImGui::End();

        ImGui::Begin("Controls");
        ImGui::SliderFloat("Zoom", &cam.zoom, 0.1f, 5.0f);
        ImGui::SliderFloat("Rotation X", &cam.rotationX, -360.0f, 360.0f);
        ImGui::SliderFloat("Rotation Y", &cam.rotationY, -360.0f, 360.0f);
        if (ImGui::Button("Reset")) { cam.reset(); }
        ImGui::End();

        ImGui::Begin("Light Properties");
        ImGui::Text("Ambient:");
        ImGui::SliderFloat("R", &lightAmbient.x, 0.0f, 1.0f);
        ImGui::SliderFloat("G", &lightAmbient.y, 0.0f, 1.0f);
        ImGui::SliderFloat("B", &lightAmbient.z, 0.0f, 1.0f);
        ImGui::SliderFloat("A", &lightAmbient.w, 0.0f, 1.0f);

        // Color picker for Diffuse ('color' is a vec4)
        ImGui::Text("Diffuse:");
        ImGui::ColorEdit3("Color", (float*)&lightDiffuse);

        // Sliders for Specular
        ImGui::Text("Specular:");
        ImGui::SliderFloat("R ", &lightSpecular.x, 0.0f, 1.0f);
        ImGui::SliderFloat("G ", &lightSpecular.y, 0.0f, 1.0f);
        ImGui::SliderFloat("B ", &lightSpecular.z, 0.0f, 1.0f);
        ImGui::SliderFloat("A ", &lightSpecular.w, 0.0f, 1.0f);
        ImGui::End();

        ImGui::Begin("Material Properties");
        // Sliders for Ambient
        ImGui::Text("Ambient:");
        ImGui::SliderFloat("R", &mat_prop.mat_ambient[0], 0.0f, 1.0f);
        ImGui::SliderFloat("G", &mat_prop.mat_ambient[1], 0.0f, 1.0f);
        ImGui::SliderFloat("B", &mat_prop.mat_ambient[2], 0.0f, 1.0f);
        ImGui::SliderFloat("A", &mat_prop.mat_ambient[3], 0.0f, 1.0f);

        // Color picker for Diffuse ('color' is a vec4)
        ImGui::Text("Diffuse:");
        ImGui::ColorEdit3("Color", (float*)&mat_prop.mat_diffuse);

        // Sliders for Specular
        ImGui::Text("Specular:");
        ImGui::SliderFloat("R ", &mat_prop.mat_specular[0], 0.0f, 1.0f);
        ImGui::SliderFloat("G ", &mat_prop.mat_specular[1], 0.0f, 1.0f);
        ImGui::SliderFloat("B ", &mat_prop.mat_specular[2], 0.0f, 1.0f);
        ImGui::SliderFloat("A ", &mat_prop.mat_specular[3], 0.0f, 1.0f);

        // Slider for Shininess
        ImGui::Text("Shininess:");
        ImGui::SliderFloat("Value", &mat_prop.mat_shininess, 1.0f, 128.0f); // Adjust max shininess as needed

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

        // Update light properties
        GLfloat light_ambient[] = { lightAmbient.x, lightAmbient.y, lightAmbient.z, lightAmbient.w };
        GLfloat light_diffuse[] = { lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, lightDiffuse.w };
        GLfloat light_specular[] = { lightSpecular.x, lightSpecular.y, lightSpecular.z, lightSpecular.w };

        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up perspective projection with GLM
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));

        // Set up view matrix (camera transformation)
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -cam.zoom));
        view = glm::rotate(view, glm::radians(cam.rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(cam.rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view));

        // Draw the selected shape
        switch (currentShape)
        {
        case CIRCLE:
            obj.drawCircle(cam, mat_prop);
            break;
        case TRIANGLE:
            obj.drawTriangle(cam, mat_prop);
            break;
        case RECTANGLE:
            obj.drawRect(cam, mat_prop);
            break;
        case SQUARE:
            obj.drawSquare(cam, mat_prop);
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
