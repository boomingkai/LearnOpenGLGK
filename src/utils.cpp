#include "utils.h"
#include <fstream>

Utils::Utils()
{
}

Utils::~Utils()
{
}

std::map<int, std::string> ErrorInfo{
	{0, "NO_ERROR"},
	{1280, "GL_INVALID_ENUM"},
	{1281, "GL_INVALID_VALUE"},
	{1282, "GL_INVALID_OPERATION"},
	{1283, "GL_STACK_OVERFLOW"},
	{1284, "GL_STACK_UNDERFLOW"},
	{1285, "GL_OUT_OF_MEMORY"},
	{1286, "GL_INVALID_FRAMEBUFFER_OPERATION"},
	{1287, "GL_CONTEXT_LOST"}
};

void Utils::checkGLError(const std::string& flag) {
	
	int code = glGetError();

	if (code != GL_NO_ERROR)
	{
		while (code != GL_NO_ERROR)
		{
			std::cerr << "ERROR CODE \"" << code << "\": " << ErrorInfo[code] << std::endl;
			code = glGetError();
		}
	}
}

std::string Utils::readShaderSource(const char* file_path)
{
	std::string content;
	std::ifstream file_stream(file_path, std::ios::in);
	std::string line = "";
	while (!file_stream.eof())
	{
		getline(file_stream, line);
		content.append(line + "\n");
	}
	file_stream.close();
	return content;
}

GLuint Utils::createShaderProgram(const char* vp, const char* fp)
{
	// ����shader
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertShaderStr = readShaderSource(vp);
	std::string fragShaderStr = readShaderSource(fp);
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();

	// ����shader source   ĩβ����Ӧ�ô��ַ�������
	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);
	// ����shader
	glCompileShader(vShader);
	glCompileShader(fShader);
	// �����������
	GLuint vfProgram = glCreateProgram();
	// ����ɫ������������
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	// ����GLSL������
	glLinkProgram(vfProgram);
	return vfProgram;
}