// opengl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "utils.h"

#define numVAOs 1
GLuint renderingPrograme;
GLuint vao[numVAOs];
float x = 0.0f;
float inc = 0.01f;

void init(GLFWwindow* window)
{
    renderingPrograme = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
    // 初始化z-buffer
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	/*x += inc;
	if (x > 1.0)
	{
		inc = -0.01f;
	}
	if (x < -1.0)
	{
		inc = 0.01f;
	}

	GLuint offsetLoc = glGetUniformLocation(renderingPrograme, "offset");
	glProgramUniform1f(renderingPrograme, offsetLoc, x);*/

    // 仅仅将着色器加载进硬件，并没有执行着色器程序
    glUseProgram(renderingPrograme);
    //glPointSize(30.0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
