#ifndef SHAPES_H
#define SHAPES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include "Material.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Define your own value of PI
#endif

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