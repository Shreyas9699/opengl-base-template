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

void Shapes::drawCircle(CameraSettings& cam, MaterialProperty& mat_prop)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_prop.mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_prop.mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_prop.mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_prop.mat_shininess);

    int numSegments = 200;
    float radius = 0.5f;
    float angleStep = 2.0f * M_PI / numSegments;

    if (this->is3D)
    {
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

                glNormal3f(x1, y1, z1);
                glVertex3f(x1, y1, z1);
                glNormal3f(x2, y2, z2);
                glVertex3f(x2, y2, z2);
            }
            glEnd();
        }
    }
    else
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
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

void Shapes::drawRect(CameraSettings& cam, MaterialProperty& mat_prop)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    // Set material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_prop.mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_prop.mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_prop.mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_prop.mat_shininess);

    float width = 1.0f;
    float height = 0.5f;

    if (this->is3D)
    {
        float depth = 0.2f;
        glBegin(GL_QUADS);

        // Front face
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);

        // Back face
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);
        glVertex3f(-width / 2, height / 2, -depth / 2);

        // Left face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(-width / 2, -height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, -depth / 2);

        // Right face
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);

        // Top face
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-width / 2, height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);

        // Bottom face
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);
        glVertex3f(-width / 2, -height / 2, depth / 2);

        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glVertex2f(-width / 2, -height / 2);
        glVertex2f(width / 2, -height / 2);
        glVertex2f(width / 2, height / 2);
        glVertex2f(-width / 2, height / 2);
        glEnd();
    }

    glPopMatrix();
}

void Shapes::drawSquare(CameraSettings& cam, MaterialProperty& mat_prop)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    // Set material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_prop.mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_prop.mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_prop.mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_prop.mat_shininess);

    float size = 0.5f;

    if (this->is3D)
    {
        glBegin(GL_QUADS);

        // Front face
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, size / 2, size / 2);
        glVertex3f(-size / 2, size / 2, size / 2);

        // Back face
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, size / 2, -size / 2);
        glVertex3f(-size / 2, size / 2, -size / 2);

        // Left face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-size / 2, -size / 2, -size / 2);
        glVertex3f(-size / 2, -size / 2, size / 2);
        glVertex3f(-size / 2, size / 2, size / 2);
        glVertex3f(-size / 2, size / 2, -size / 2);

        // Right face
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, -size / 2, size / 2);
        glVertex3f(size / 2, size / 2, size / 2);
        glVertex3f(size / 2, size / 2, -size / 2);

        // Top face
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-size / 2, size / 2, -size / 2);
        glVertex3f(size / 2, size / 2, -size / 2);
        glVertex3f(size / 2, size / 2, size / 2);
        glVertex3f(-size / 2, size / 2, size / 2);

        // Bottom face
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, -size / 2, -size / 2);
        glVertex3f(size / 2, -size / 2, size / 2);
        glVertex3f(-size / 2, -size / 2, size / 2);

        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);
        glVertex2f(-size / 2, -size / 2);
        glVertex2f(size / 2, -size / 2);
        glVertex2f(size / 2, size / 2);
        glVertex2f(-size / 2, size / 2);
        glEnd();
    }

    glPopMatrix();
}

void Shapes::drawTriangle(CameraSettings& cam, MaterialProperty& mat_prop)
{
    glPushMatrix();
    applyZoomAndRotation(cam);

    // Set material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_prop.mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_prop.mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_prop.mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat_prop.mat_shininess);

    float base = 1.0f;
    float height = 1.0f;

    if (this->is3D)
    {
        glBegin(GL_TRIANGLES);

        // Front face
        glNormal3f(0.0f, 0.5f, 0.5f);
        glVertex3f(0.0f, height / 2, 0.0f);
        glVertex3f(-base / 2, -height / 2, base / 2);
        glVertex3f(base / 2, -height / 2, base / 2);

        // Right face
        glNormal3f(0.5f, 0.5f, 0.0f);
        glVertex3f(0.0f, height / 2, 0.0f);
        glVertex3f(base / 2, -height / 2, base / 2);
        glVertex3f(base / 2, -height / 2, -base / 2);

        // Back face
        glNormal3f(0.0f, 0.5f, -0.5f);
        glVertex3f(0.0f, height / 2, 0.0f);
        glVertex3f(base / 2, -height / 2, -base / 2);
        glVertex3f(-base / 2, -height / 2, -base / 2);

        // Left face
        glNormal3f(-0.5f, 0.5f, 0.0f);
        glVertex3f(0.0f, height / 2, 0.0f);
        glVertex3f(-base / 2, -height / 2, -base / 2);
        glVertex3f(-base / 2, -height / 2, base / 2);

        glEnd();

        glBegin(GL_QUADS);
        // Bottom face
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-base / 2, -height / 2, -base / 2);
        glVertex3f(base / 2, -height / 2, -base / 2);
        glVertex3f(base / 2, -height / 2, base / 2);
        glVertex3f(-base / 2, -height / 2, base / 2);
        glEnd();
    }
    else
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(-base / 2, -height / 2);
        glVertex2f(base / 2, -height / 2);
        glVertex2f(0.0f, height / 2);
        glEnd();
    }

    glPopMatrix();
}
