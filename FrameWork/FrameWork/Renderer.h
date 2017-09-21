#pragma once

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

public:
	void Initialize();

public:
	void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);
public:
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);

	//Shader
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
private:
	GLuint m_SolidRectShader;
	GLuint m_VBORect ;
};

