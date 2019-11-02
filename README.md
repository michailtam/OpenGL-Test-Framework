# OpenGL Test Framework

This is a ready to use OpenGL Framework, which can be used, to test different kinds of CG algorithms, shaders, basic and advanced CG (computer graphics) techniques. The framework was implemented in C/C++ using Visual Studio 2017 and the STL library (no OOP). In its default implementation the application displays as an example a triangle with interpolated colors and the viewport dimensions are of size 1920 x 1080. Feel free to use the framework and adjust it to your purposes. 

### IMPORTANT: Because this is only a test framework, which was developed for rapid prototyping CG algorithms, all the memory and security management operations like exception handling, auto pointers etc. and most comments are missing. Nevertheless, if you like you can extend the framework and implement them yourself. 

## Content Description
The OpenGL framework consists of the following files, libraries and folders:
* main.cpp: The main C++ file (starting point)
* models.h: A library containing operations to read data of the model (i.e. vertices, colors, etc.)
* shaders.h: A library containing all the shader management (i.e. creating vertex and fragment shaders, etc.) 
* models folder: Contains the model data
* shaders folder: Contains the shader contents

## Usage
To use this framework you have to download the following libraries and set them up in your prefered development environment (I have used the following versions glfw-3.3, glm-0.9.9.6, [GLAD](https://glad.dav1d.de/)):
1. GLM: An open-source mathematics framework especially developed for OpenGL and well tested
2. GLFW: An open-source framework to handle all the OS specific tasks like keyboard and mouse events
3. GLAD: Contains all the operations to get the available OpenGL extensions accorging to the system

### NOTE: You can take a look of how to setup these libraries at [Learnopengl](https://learnopengl.com/Introduction). This is by the way an awesome tutorial, to start learning OpenGL. It describes and implements many CG techniques frequently used in computer games and computer graphics in general. If you want to learn in a practical way how to program CG applications with OpenGL, I highly recommend this.