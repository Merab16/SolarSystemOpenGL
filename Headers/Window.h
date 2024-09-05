#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


namespace MyWindow {
	class Window {
	private:
		GLFWwindow* pWindow_;


	private:
		void RegisterCallbacks();

	public:
		Window(size_t width, size_t height, const std::string& wName);
		~Window();


		void Run();

	};



}