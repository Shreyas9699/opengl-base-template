#ifndef SHAPES_H
#define SHAPES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

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
	ImVec4 color;
	bool is3D;

	Shapes(ImVec4 col, bool flg)
		: color(col), is3D(flg) {}

	void applyZoomAndRotation(CameraSettings& cam);
	void drawCircle(CameraSettings& cam);
	void drawRect(CameraSettings& cam);
	void drawSquare(CameraSettings& cam);
	void drawTriangle(CameraSettings& cam);
};

#endif // SHAPES_H