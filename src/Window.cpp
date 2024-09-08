#include "Window.h"

#include <stdexcept>
#include <iostream>

#include "Render/ShaderProgram.h"



// callbacks
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}


GLfloat points[] = {
	0.f, 0.5f, 0.f,
	0.5f, -0.5f, 0.f,
	-0.5f, -0.5f, 0.f
};

GLfloat colors[] = {
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f
};

namespace MyWindow {
	Window::Window(size_t width, size_t height, const std::string& wName,
		const std::string& exePath)
		: resourceManager_(exePath)
	{
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
		auto pDefaultShaderProgram = resourceManager_.LoadShaders(
			"DefaultShader",
			"res/Shaders/vertex.txt",
			"res/Shaders/fragment.txt");

		if (!pDefaultShaderProgram) {
			throw std::logic_error("Can't create shader program: DefaultShader");
		}

		GLuint points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);



		while (!glfwWindowShouldClose(pWindow_))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			pDefaultShaderProgram->Use();
			glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES, 0, 3);  


			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow_);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}



}