#ifndef Demo_GLSL_Program_H_
#define Demo_GLSL_Program_H_

#include <string>
#include <glew.h>

class GLSLProgram {
private:
	GLuint		 _programID;
	GLuint		_vertexShaderID;
	GLuint		_fragmentShaderID;
	int			_numAttributes;

public:
    GLSLProgram();
	~GLSLProgram();

private:
	void compileShader(const std::string& filePath, GLuint id);

public:
    void compileShaders(const std::string& vSPath, const std::string& fSpath);
	void linkShaders();
    void addAttribute(const std::string& attributeName);
	GLuint getUniformLocation(const std::string& uniformName);
    void use();
    void unuse();
};

#endif

