#include "ResourceManager.h"
#include "../Render/ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>


namespace Resources {

	ResourceManager::ResourceManager(const std::string executablePath) {
		size_t last_slash = executablePath.find_last_of("/\\");
		path_ = executablePath.substr(0, last_slash);
		std::cout << path_ << std::endl;


	}




	// private
	std::string ResourceManager::GetFileString(const std::string& relativePath) {
		std::ifstream fin(path_ + '/' + relativePath, std::ios::in | std::ios::binary);
		if (!fin.is_open()) {
			throw std::invalid_argument("Can't open " + relativePath);
		}

		std::stringstream buf;
		buf << fin.rdbuf();

		return buf.str();
	}


	// public
	std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(
		const std::string& shaderName,
		const std::string& vertexPath,
		const std::string& fragmentPath) {

		std::string vertexString = GetFileString(vertexPath);
		std::string fragmentString = GetFileString(fragmentPath);

		auto res = shaderPrograms_.emplace(shaderName,
			std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString));
		
		auto& newShader = res.first->second;
		if (!newShader->IsComplied())
			throw std::logic_error("Failed to compile shader: " + shaderName);

		return newShader;
	}


	std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(
		const std::string& shaderName) {

		auto it = shaderPrograms_.find(shaderName);
		if (it == shaderPrograms_.end()) {
			throw std::logic_error("Can't find shader: " + shaderName);
		}
		return it->second;
	}


}



