#pragma once
#include <string>
#include <glew.h>

namespace C3Engine
{
	class GLSLProgram
	{
		public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();

		void addAttribute(const std::string attributeName);

		void use();
		void unuse();

		GLint getUniformLocation(const std::string& uniformName);

		private:
		int _numAttributes;

		GLuint _programID;

		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void compileShader(const std::string filePath, GLuint id);
	};
}