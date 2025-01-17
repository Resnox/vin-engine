#include "program_opengl.hpp"

#include "core/assert.hpp"
#include "logger/logger.hpp"

#include "glad/gl.h"

static unsigned int currentlyBindedProgram{ 0 };

Vin::OpenGLProgram::OpenGLProgram()
{
	m_ProgramId = glCreateProgram();
	for (int i = 0; i < m_ShaderCount; ++i)
		glDeleteShader(m_Shaders[i]);
}

Vin::OpenGLProgram::~OpenGLProgram()
{
	glDeleteProgram(m_ProgramId);
}

void Vin::OpenGLProgram::Bind()
{
	if (currentlyBindedProgram != m_ProgramId) {
		glUseProgram(m_ProgramId);
		currentlyBindedProgram = m_ProgramId;
	}
}

void Vin::OpenGLProgram::Unbind()
{
	glUseProgram(0);
}

bool Vin::OpenGLProgram::AddShader(ShaderType type, const char* src)
{
	unsigned int shaderId;
	shaderId = glCreateShader(ParseShaderType(type));
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);
	if (!CheckForShaderCompilationErr(shaderId)) {
		m_IsShaderComplete = false;
		return false;
	}
	m_Shaders[m_ShaderCount] = shaderId;
	++m_ShaderCount;
	return true;
}

bool Vin::OpenGLProgram::CompileProgram()
{
	for (int i = 0; i < m_ShaderCount; ++i)
		glAttachShader(m_ProgramId, m_Shaders[i]);

	glLinkProgram(m_ProgramId);
	if (!CheckForProgramCompilationErr(m_ProgramId))
		return false;

	for (int i = 0; i < m_ShaderCount; ++i)
		glDeleteShader(m_Shaders[i]);

	m_IsProgramComplete = true;
	m_ShaderCount = 0;

	return true;
}

bool Vin::OpenGLProgram::IsProgramComplete()
{
	return m_IsProgramComplete && m_IsShaderComplete;
}

int Vin::OpenGLProgram::GetField(const char* name)
{
	return glGetUniformLocation(m_ProgramId, name);
}

void Vin::OpenGLProgram::SetFloat(int location, float value)
{
	Bind();
	glUniform1f(location, value);
}

void Vin::OpenGLProgram::SetFloat2(int location, float* values)
{
	Bind();
	glUniform2f(location, values[0], values[1]);
}

void Vin::OpenGLProgram::SetFloat3(int location, float* values)
{
	Bind();
	glUniform3f(location, values[0], values[1], values[2]);
}

void Vin::OpenGLProgram::SetFloat4(int location, float* values)
{
	Bind();
	glUniform4f(location, values[0], values[1], values[2], values[3]);
}

void Vin::OpenGLProgram::SetFloats(int location, float* values, size_t count)
{
	Bind();
	glUniform1fv(location, count, values);
}

void Vin::OpenGLProgram::SetInt(int location, int value)
{
	Bind();
	glUniform1i(location, value);
}

void Vin::OpenGLProgram::SetInt2(int location, int* values)
{
	Bind();
	glUniform2i(location, values[0], values[1]);
}

void Vin::OpenGLProgram::SetInt3(int location, int* values)
{
	Bind();
	glUniform3i(location, values[0], values[1], values[2]);
}

void Vin::OpenGLProgram::SetInt4(int location, int* values)
{
	Bind();
	glUniform4i(location, values[0], values[1], values[2], values[3]);
}

void Vin::OpenGLProgram::SetInts(int location, int* values, size_t count)
{
	Bind();
	glUniform1iv(location, count, values);
}

void Vin::OpenGLProgram::SetMat3(int location, float* values)
{
	Bind();
	glUniformMatrix3fv(location, 1, GL_FALSE, values);
}

void Vin::OpenGLProgram::SetMat4(int location, float* values)
{
	Bind();
	glUniformMatrix4fv(location, 1, GL_FALSE, values);
}

int Vin::OpenGLProgram::ParseShaderType(ShaderType type)
{
	switch (type) {
	case ShaderType::ComputeShader: return GL_COMPUTE_SHADER;
	case ShaderType::VertexShader: return GL_VERTEX_SHADER;
	case ShaderType::TessControl: return GL_TESS_CONTROL_SHADER;
	case ShaderType::TessEvaluation: return GL_TESS_EVALUATION_SHADER;
	case ShaderType::GeometryShader: return GL_GEOMETRY_SHADER;
	case ShaderType::FragmentShader: return GL_FRAGMENT_SHADER;
	}
	return -1;
}

bool Vin::OpenGLProgram::CheckForShaderCompilationErr(unsigned int shaderId)
{
	int result;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		Logger::Err("Shader compilation error : {}", infoLog);
		return false;
	}
	return true;
}

bool Vin::OpenGLProgram::CheckForProgramCompilationErr(unsigned int programId)
{
	int result{ 0 };
	char infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		Logger::Err("Program compilation error : {}", infoLog);
		return false;
	}
	return true;
}
