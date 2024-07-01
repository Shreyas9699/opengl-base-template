#ifndef SHAPES_H
#define SHAPES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Define your own value of PI
#endif

struct MaterialProperty 
{
	GLfloat mat_ambient[4];  // Array for ambient color (RGBA)
	GLfloat mat_diffuse[4];  // Array for diffuse color (RGBA)
	GLfloat mat_specular[4]; // Array for specular color (RGBA)
	GLfloat mat_shininess;   // Shininess value

	// Constructor to set material properties
	MaterialProperty(GLfloat amb_r = 0.2f, GLfloat amb_g = 0.2f, GLfloat amb_b = 0.2f, GLfloat amb_a = 1.0f,
		GLfloat diff_r = 1.0f, GLfloat diff_g = 1.0f, GLfloat diff_b = 1.0f, GLfloat diff_a = 1.0f,
		GLfloat spec_r = 0.5f, GLfloat spec_g = 0.5f, GLfloat spec_b = 0.5f, GLfloat spec_a = 1.0f,
		GLfloat shine = 32.0f)
	{
		mat_ambient[0] = amb_r;
		mat_ambient[1] = amb_g;
		mat_ambient[2] = amb_b;
		mat_ambient[3] = amb_a;

		mat_diffuse[0] = diff_r;
		mat_diffuse[1] = diff_g;
		mat_diffuse[2] = diff_b;
		mat_diffuse[3] = diff_a;

		mat_specular[0] = spec_r;
		mat_specular[1] = spec_g;
		mat_specular[2] = spec_b;
		mat_specular[3] = spec_a;

		mat_shininess = shine;
	}
};

struct CameraSettings
{
	float zoom = 1.0f;
	float rotationX = 0.0f;
	float rotationY = 0.0f;
	bool isDragging = false;
	double lastX = 0, lastY = 0;

	void reset()
	{
		zoom = 1.0f;
		rotationX = 0.0f;
		rotationY = 0.0f;
		isDragging = false;
		lastX = 0, lastY = 0;
	}
};

class Shapes
{
public:
	bool is3D;

	Shapes(bool flg)
		: is3D(flg) {}

	void applyZoomAndRotation(CameraSettings& cam);
	void drawCircle(CameraSettings& cam, MaterialProperty& mat_prop);
	void drawRect(CameraSettings& cam, MaterialProperty& mat_prop);
	void drawSquare(CameraSettings& cam, MaterialProperty& mat_prop);
	void drawTriangle(CameraSettings& cam, MaterialProperty& mat_prop);
};

#endif // SHAPES_H