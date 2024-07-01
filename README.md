# OpenGL base template: A Reusable Base for Your OpenGL Projects

This repository provides a well-structured and customizable base template for developing OpenGL applications in Visual Studio C++ using GLFW, GLEW, ImGui, and GLM. 
It offers a streamlined setup and boilerplate code to kickstart your projects quickly.


## Getting Started

1. Clone the Repository:
	Use Git to clone this repository to your local machine: <br />
	&nbsp;`git clone https://github.com/Shreyas9699/opengl-base-template.git`
	
	Or download the Zip file and extract its contents from github repo page.
	
2. Once its downloaded, double click on the `opengl-base-template.sln` file to open the project in Visual Studio.

3. Make sure that you change the architecture to `Win32` in Visual Studio — this is required or else your project won't compile.

4. U can build and run the main.cpp to see a sample 2D/3D geometry rendering example.


## Change the project name

1. Change below files with the desired project name, <br />
&nbsp;lets say new project name is `proj-new-name`, then update below files: <br />
	* `opengl-base-template.sln` to `proj-new-name.sln`
	* `opengl-base-template.filters` to `proj-new-name.filters`
	* `opengl-base-template.user` to `proj-new-name.user`
	* `opengl-base-template.vcxproj` to `proj-new-name.vcxproj`
	* `opengl-base-template.vcxproj.user` to `proj-new-name.vcxproj.user`

2. Change the project folder name as well to `proj-new-name` the director where the `sln` file is present

3. In the `proj-new-name.sln`, update the Project value from `opengl-base-template\opengl-base-template.vcxproj` to `proj-new-name\proj-new-name.vcxproj`

4. Now open the  double click on the `proj-new-name.sln` file, and you should be able to run it under new project name. (_make sure to change the architecture to `Win32`_)

## Sample application (2D and 3D rendering)
### Description

A simple rendering application that uses OpenGL and Dear ImGUI to render 2D and 3D shapes and allow user to select different shapes, properties such as light and material, etc.
Below is the demo video of application in use.

https://github.com/Shreyas9699/opengl-base-template/assets/63774467/79d4212a-b184-4613-8c01-6696e7cb78bd

