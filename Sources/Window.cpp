#include "../Headers/Window.h"

#include <stdexcept>
#include <iostream>

#include "../Render/Headers/ShaderProgram.h"


// callbacks
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"	color = vertex_color;"
"	gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"	frag_color = vec4(color, 1.0);"
"}";

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
		std::string vShader(vertex_shader);
		std::string fShader(fragment_shader);
		Renderer::ShaderProgram shaderProgram(vertex_shader, fragment_shader);
		if (!shaderProgram.IsComplied()) {
			throw std::logic_error("Cant create shader program");
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
			shaderProgram.Use();
			glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES, 0, 3);  


			/* Swap front and back buffers */
			glfwSwapBuffers(pWindow_);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}



}