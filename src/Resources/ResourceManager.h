#pragma once
#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderProgram;
}


namespace Resources {

	class ResourceManager {
	private:
		using ShaderProgramsMap = std::map<const std::string,
			std::shared_ptr<Renderer::ShaderProgram>>;
		ShaderProgramsMap shaderPrograms_;

		std::string path_;

	private:
		std::string GetFileString(const std::string& relativePath);



	public:
		ResourceManager(const std::string executablePath);
		~ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator= (const ResourceManager&) = delete;

		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator= (ResourceManager&&) = delete;

		std::shared_ptr<Renderer::ShaderProgram> LoadShaders(
			const std::string& shaderName,
			const std::string& vertexPath,
			const std::string& fragmentPath);
		std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(
			const std::string& shaderName);



	};




}