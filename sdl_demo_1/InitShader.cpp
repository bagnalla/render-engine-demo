#define _CRT_SECURE_NO_DEPRECATE
//#include "Angel.h"
//#include <cmath>
#include "Util.h"
#include <iostream>
#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <GL/gl.h>

namespace Bagnall {

	// Create a NULL-terminated string by reading the provided file
	static char*
		readShaderSource(const char* shaderFile)
	{
			FILE* fp = fopen(shaderFile, "r");

			if (fp == NULL) { return NULL; }

			fseek(fp, 0L, SEEK_END);
			long size = ftell(fp);

			fseek(fp, 0L, SEEK_SET);
			char* buf = new char[size + 1];
			fread(buf, 1, size, fp);

			buf[size] = '\0';
			fclose(fp);

			return buf;
		}


	// Create a GLSL program object from vertex and fragment shader files
	GLuint
		InitShader(const char* vShaderFile, const char* fShaderFile)
	{
		struct Shader {
			const char*  filename;
			GLenum       type;
			GLchar*      source;
		}  shaders[2] = {
			{ vShaderFile, GL_VERTEX_SHADER, NULL },
			{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
		};

		GLuint program = glCreateProgram();

		for (int i = 0; i < 2; ++i) {
			Shader& s = shaders[i];
			//s.source = readShaderSource(s.filename);
			auto source = Util::ReadAllBytes(s.filename);
			source.push_back('\0');
			s.source = source.data();
			if (shaders[i].source == NULL) {
				std::cerr << "Failed to read " << s.filename << std::endl;
				system("pause");
				exit(EXIT_FAILURE);
			}

			GLuint shader = glCreateShader(s.type);
			glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
			glCompileShader(shader);

			GLint  compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				std::cerr << s.filename << " failed to compile:" << std::endl;
				GLint  logSize;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
				char* logMsg = new char[logSize];
				glGetShaderInfoLog(shader, logSize, NULL, logMsg);
				std::cerr << logMsg << std::endl;
				delete[] logMsg;

				system("pause");
				exit(EXIT_FAILURE);
			}

			//delete[] s.source;

			glAttachShader(program, shader);
		}

		/* link  and error check */
		glLinkProgram(program);

		GLint  linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			std::cerr << "Shader program " << vShaderFile << ", " << fShaderFile << " failed to link" << std::endl;
			GLint  logSize;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog(program, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			system("pause");
			exit(EXIT_FAILURE);
		}

		/* use program object */
		glUseProgram(program);

		return program;
	}

	// Create a GLSL program object from vertex shader file
	GLuint
		InitShader(const char* vShaderFile)
	{
		struct Shader {
			const char*  filename;
			GLenum       type;
			GLchar*      source;
		}  shaders[2] = {
			{ vShaderFile, GL_VERTEX_SHADER, NULL }
		};

		GLuint program = glCreateProgram();

		for (int i = 0; i < 1; ++i) {
			Shader& s = shaders[i];
			s.source = readShaderSource(s.filename);
			if (shaders[i].source == NULL) {
				std::cerr << "Failed to read " << s.filename << std::endl;
				system("pause");
				exit(EXIT_FAILURE);
			}

			GLuint shader = glCreateShader(s.type);
			glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
			glCompileShader(shader);

			GLint  compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				std::cerr << s.filename << " failed to compile:" << std::endl;
				GLint  logSize;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
				char* logMsg = new char[logSize];
				glGetShaderInfoLog(shader, logSize, NULL, logMsg);
				std::cerr << logMsg << std::endl;
				delete[] logMsg;

				system("pause");
				exit(EXIT_FAILURE);
			}

			delete[] s.source;

			glAttachShader(program, shader);
		}

		/* link  and error check */
		glLinkProgram(program);

		GLint  linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			std::cerr << "Shader program " << vShaderFile << " failed to link" << std::endl;
			GLint  logSize;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog(program, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			system("pause");
			exit(EXIT_FAILURE);
		}

		/* use program object */
		glUseProgram(program);

		return program;
	}

}  // Close namespace Angel block
