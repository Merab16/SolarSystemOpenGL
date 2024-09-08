#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Resources/ResourceManager.h"

namespace MyWindow {
	class Window {
	private:
		GLFWwindow* pWindow_;
		Resources::ResourceManager resourceManager_;

	private:
		void RegisterCallbacks();

	public:
		Window(size_t width, size_t height, const std::string& wName,
			const std::string& exePath);
		~Window();


		void Run();

	};



}