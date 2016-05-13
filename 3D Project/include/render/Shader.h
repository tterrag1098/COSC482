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
	Shader();

	void loadFile(const GLchar* vertexPath, const GLchar* fragmentPath);
	void load(const GLchar* vertex, const GLchar* frag);

  	// Use the program
  	void use() const;
};

#endif
