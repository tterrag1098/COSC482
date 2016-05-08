#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
  	// The program ID
	GLuint program;
	// Constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
  	// Use the program
  	void use();
};

#endif
