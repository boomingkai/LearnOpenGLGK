// opengl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include <map>

#define numVAOs 1
GLuint renderingPrograme;
GLuint vao[numVAOs];

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

void checkGLError(const std::string& flag = "NO_FLAG") {
	int code = glGetError();

	if (code != GL_NO_ERROR) {
		if (flag != "NO_FLAG") {
			std::cout << "OpenGL ERROR at flag \"" << flag << "\"\n";
		}

		while (code != GL_NO_ERROR) {
			std::cerr << "ERROR CODE \"" << code << "\": " << ErrorInfo[code] << std::endl;
			code = glGetError();
		}
	}
}


GLuint createShaderProgram()
{
    // shader源码
    const char* vshaderSource =
        "#version 430 \n"
        "void main(void)\n"
        "{ gl_Position = vec4(0.0,0.0,0.0,1.0);}";
        
    const char* fshaderSource =
        "#version 430 \n"
        "out vec4 color;\n"
        "void main(void) \n"
        "{ color = vec4(1.0,0.0,0.0,1.0); }";

    // 创建shader
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 关联shader source
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    // 编译shader
    glCompileShader(vShader);
	glCompileShader(fShader);
    // 创建程序对象
    GLuint vfProgram = glCreateProgram();
    // 将着色器加入程序对象
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    // 请求GLSL编译器
    glLinkProgram(vfProgram);
    return vfProgram;
}

void init(GLFWwindow* window)
{
    renderingPrograme = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
    // 仅仅将着色器加载进硬件，并没有执行着色器程序
    glUseProgram(renderingPrograme);
    glPointSize(30.0);
    glDrawArrays(GL_POINTS, 0, 1);
    /*glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);*/
}

int main()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - programe1", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        exit(EXIT_FAILURE);
    }
    init(window);
    while (!glfwWindowShouldClose(window))
    {
        display(window,glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
