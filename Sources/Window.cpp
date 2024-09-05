#include "../Headers/Window.h"

#include <stdexcept>
#include <iostream>

// callbacks
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}

namespace MyWindow {
	Window::Window(size_t width, size_t height, const std::string& wName) {
		if (!glfwInit()) {
			throw std::logic_error("Error init GLFW");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		

		pWindow_ = glfwCreateWindow(width, height, wName.c_str(), NULL, NULL);
		if (!pWindow_)
		{
			glfwTerminate();
			throw std::logic_error("Error create window");
		}
		RegisterCallbacks();
		glfwMakeContextCurrent(pWindow_);

		if (!gladLoadGL()) {
			throw std::logic_error("Error load GLAD");
		}

		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;


		glClearColor(0, 1, 1, 1);

	}

	Window::~Window() {
		glfwTerminate();
	}
	



	// private
	void Window::RegisterCallbacks() {
		glfwSetKeyCallback(pWindow_, glfwKeyCallback);
	}


	// public
	void Window::Run() {
		while (!glfwWindowShouldClose(pWindow_))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow_);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}



}