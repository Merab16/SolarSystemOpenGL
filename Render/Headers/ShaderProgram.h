#pragma once
#include <glad/glad.h>

#include <string>



namespace Renderer {

	class ShaderProgram {
	private:
		bool isCompiled_ = false;
		GLuint id_ = 0;

	private:
		bool CreateShader(const std::string& source,
			const GLuint shaderType,GLuint& shader);


	public:
		ShaderProgram(const std::string& vertexShader,
			const std::string& fragmentShader);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		
		// move semantic
		ShaderProgram& operator=(ShaderProgram&&) noexcept;
		ShaderProgram (ShaderProgram&&) noexcept;

		void Use() const;


		// getters
		bool IsComplied() const { return isCompiled_; }
		
	};




}