#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Define your own value of PI
#endif

int windowWidth = 1440;
int windowHeight = 800;

float zoom = 1.0f;
float rotationX = 0.0f;
float rotationY = 0.0f;
bool isDragging = false;
double lastX = 0, lastY = 0;
bool is3D = false;

void applyZoomAndRotation()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glScalef(zoom, zoom, zoom);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
}

void drawCircle(ImVec4& color, bool is3D)
{
    glPushMatrix();
    applyZoomAndRotation();

    glColor4f(color.x, color.y, color.z, color.w);
    int numSegments = 200;
    float radius = 0.5f;
    float angleStep = 2.0f * M_PI / numSegments;

    if (is3D) 
    {
        // Draw a sphere
        for (int j = 0; j <= numSegments; j++) 
        {
            float theta1 = j * M_PI / numSegments;
            float theta2 = (j + 1) * M_PI / numSegments;

            glBegin(GL_QUAD_STRIP);

            for (int i = 0; i <= numSegments; i++) 
            {
                float phi = i * angleStep;

                float x1 = radius * cos(phi) * sin(theta1);
                float y1 = radius * sin(phi) * sin(theta1);
                float z1 = radius * cos(theta1);

                float x2 = radius * cos(phi) * sin(theta2);
                float y2 = radius * sin(phi) * sin(theta2);
                float z2 = radius * cos(theta2);

                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
            }
            glEnd();
        }
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // Center of circle
        for (int i = 0; i <= numSegments; i++)
        {
            float newX = radius * cos(angleStep * i);
            float newY = radius * sin(angleStep * i);
            glVertex2f(newX, newY);
        }
        glEnd();
    }

    glPopMatrix();
}

void drawRect(ImVec4& color, bool is3D)
{
    glPushMatrix();
    applyZoomAndRotation();

    glColor4f(color.x, color.y, color.z, color.w);

    if (is3D) 
    {
        // Draw a cuboid
        float width = 1.0f;   // Width of the cuboid
        float height = 0.5f;  // Height of the cuboid
        float depth = 0.3f;   // Depth of the cuboid

        glBegin(GL_QUADS);
        // Front face
        glVertex3f(-width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);

        // Back face
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(-width / 2, height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, -depth / 2);

        // Top face
        glVertex3f(-width / 2, height / 2, -depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);

        // Bottom face
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);
        glVertex3f(-width / 2, -height / 2, depth / 2);

        // Right face
        glVertex3f(width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);

        // Left face
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(-width / 2, -height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, -depth / 2);

        glEnd();
    }
    else 
    {
        glBegin(GL_QUADS);
        glVertex2f(-0.75f, 0.25f);  // Top-left
        glVertex2f(0.75f, 0.25f);   // Top-right
        glVertex2f(0.75f, -0.25f);  // Bottom-right
        glVertex2f(-0.75f, -0.25f); // Bottom-left
        glEnd();
    }

    glPopMatrix();
}

void drawSquare(ImVec4& color, bool is3D)
{
    glPushMatrix();
    applyZoomAndRotation();

    glColor4f(color.x, color.y, color.z, color.w);
    float size = 0.5f;  // Half the size of the square

    if (is3D) 
    {
        // Draw a cube
        glBegin(GL_QUADS);
        // Front face
        glVertex3f(-size, -size, size);
        glVertex3f(size, -size, size);
        glVertex3f(size, size, size);
        glVertex3f(-size, size, size);
        // Back face
        glVertex3f(-size, -size, -size);
        glVertex3f(-size, size, -size);
        glVertex3f(size, size, -size);
        glVertex3f(size, -size, -size);
        // Top face
        glVertex3f(-size, size, -size);
        glVertex3f(-size, size, size);
        glVertex3f(size, size, size);
        glVertex3f(size, size, -size);
        // Bottom face
        glVertex3f(-size, -size, -size);
        glVertex3f(size, -size, -size);
        glVertex3f(size, -size, size);
        glVertex3f(-size, -size, size);
        // Right face
        glVertex3f(size, -size, -size);
        glVertex3f(size, size, -size);
        glVertex3f(size, size, size);
        glVertex3f(size, -size, size);
        // Left face
        glVertex3f(-size, -size, -size);
        glVertex3f(-size, -size, size);
        glVertex3f(-size, size, size);
        glVertex3f(-size, size, -size);
        glEnd();
    }
    else 
    {
        glBegin(GL_QUADS);
        glVertex2f(-size, size);   // Top-left
        glVertex2f(size, size);    // Top-right
        glVertex2f(size, -size);   // Bottom-right
        glVertex2f(-size, -size);  // Bottom-left
        glEnd();
    }

    glPopMatrix();
}

void drawTriangle(ImVec4& color, bool is3D)
{
    glPushMatrix();
    applyZoomAndRotation();

    glColor4f(color.x, color.y, color.z, color.w);

    if (is3D) 
    {
        // Draw a tetrahedron
        glBegin(GL_TRIANGLES);
        // Front face
        glVertex3f(0.0f, 0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        // Right face
        glVertex3f(0.0f, 0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.0f, -0.5f, -0.5f);
        // Left face
        glVertex3f(0.0f, 0.5f, 0.0f);
        glVertex3f(0.0f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        // Bottom face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.0f, -0.5f, -0.5f);
        glEnd();
    }
    else 
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
    }

    glPopMatrix();
}

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
            isDragging = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        }
        else if (action == GLFW_RELEASE) 
        {
            isDragging = false;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoom += yoffset * 0.1f;
    zoom = std::max(0.1f, std::min(zoom, 5.0f));
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
    ImVec4 shape_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

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
        ImGui::ColorEdit3("Shape Color", (float*)&shape_color);
        ImGui::Checkbox("3D Mode", &is3D);
        ImGui::End();

        ImGui::Begin("Controls");
        ImGui::SliderFloat("Zoom", &zoom, 0.1f, 5.0f);
        ImGui::SliderFloat("Rotation X", &rotationX, -360.0f, 360.0f);
        ImGui::SliderFloat("Rotation Y", &rotationY, -360.0f, 360.0f);
        ImGui::End();

        // Handle mouse dragging for rotation
        if (isDragging)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            double dx = xpos - lastX;
            double dy = ypos - lastY;
            rotationY += dx * 0.5f;
            rotationX += dy * 0.5f;
            lastX = xpos;
            lastY = ypos;
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
            drawCircle(shape_color, is3D);
            break;
        case TRIANGLE:
            drawTriangle(shape_color, is3D);
            break;
        case RECTANGLE:
            drawRect(shape_color, is3D);
            break;
        case SQUARE:
            drawSquare(shape_color, is3D);
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