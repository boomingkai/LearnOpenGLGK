#include <string>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <map>




class Utils
{
public:
	Utils();
	~Utils();
	static void checkGLError(const std::string& flag = "NO_FLAG");
	static std::string readShaderSource(const char* file_path);
	static GLuint createShaderProgram(const char* vp, const char* fp);

};

