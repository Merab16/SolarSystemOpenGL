#include "../Headers/ShaderProgram.h"
#include <iostream>

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertShader = 0;
		if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertShader)) {
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			return;
		}

		GLuint fragShader = 0;
		if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragShader)) {
			std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
			glDeleteShader(vertShader);
			return;
		}

		id_ = glCreateProgram();
		glAttachShader(id_, vertShader);
		glAttachShader(id_, fragShader);
		glLinkProgram(id_);

		GLint success;
		glGetProgramiv(id_, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(id_, 1024, nullptr, infoLog);
			std::cerr << "SHADER ERROR: Link time error:\n" << infoLog << std::endl;
		}
		else {
			isCompiled_ = true;
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(id_);
	}

	// move semantic
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept {
		glDeleteProgram(id_);
		id_ = rhs.id_;
		isCompiled_ = rhs.isCompiled_;

		rhs.id_ = 0;
		rhs.isCompiled_ = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept {
		id_ = rhs.id_;
		isCompiled_ = rhs.isCompiled_;

		rhs.id_ = 0;
		rhs.isCompiled_ = false;
	}


	// private
	bool ShaderProgram::CreateShader(const std::string& source, const GLuint shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "SHADER ERROR: Compile time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;

	}


	// public
	void ShaderProgram::Use() const {
		glUseProgram(id_);
	}


}