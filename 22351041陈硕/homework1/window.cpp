#include "window.h"

//std
#include <stdexcept>

Window::Window(int w, int h, std::string name) : width(w), height(h), windowName(name)
{
	initWindow();
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Window::frambufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto lvewindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	lvewindow->frambufferResized = true;
	lvewindow->width = width;
	lvewindow->height = height;
}

void Window::initWindow()
{
	//��ʼ��
	glfwInit();
	//�������汾�źʹ˰汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//����profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//��������
	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	//����Ϊ��Ҫ��������
	glfwMakeContextCurrent(window);
	//set to be the parent window object
	glfwSetWindowUserPointer(window, this);
	//���贰�ڴ�С
	glfwSetFramebufferSizeCallback(window, frambufferResizeCallback);
}



