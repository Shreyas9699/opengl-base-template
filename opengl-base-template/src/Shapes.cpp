#include "Shapes.h"
#include <cmath>

void Shapes::applyZoomAndRotation(CameraSettings& cam)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glScalef(cam.zoom, cam.zoom, cam.zoom);
    glRotatef(cam.rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(cam.rotationY, 0.0f, 1.0f, 0.0f);
}

void Shapes::drawCircle(CameraSettings& cam)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);
    int numSegments = 200;
    float radius = 0.5f;
    float angleStep = 2.0f * M_PI / numSegments;

    if (this->is3D)
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

void Shapes::drawRect(CameraSettings& cam)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

    if (this->is3D)
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

void Shapes::drawSquare(CameraSettings& cam)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);
    float size = 0.5f;  // Half the size of the square

    if (this->is3D)
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

void Shapes::drawTriangle(CameraSettings& cam)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    glColor4f(this->color.x, this->color.y, this->color.z, this->color.w);

    if (this->is3D)
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