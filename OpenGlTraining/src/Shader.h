#pragma once
#include <string>
#include <unordered_map>
struct ShaderSource {
	std::string vertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath; // just for debug i think
	// caching for unifroms
	std::unordered_map<std::string, int> m_UniformLoactionCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name,int value);
	void SetUniform1f(const std::string& name,float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);// convert to vec4 when using math
private:
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderSource ParseShader(const std::string& filepath);
	int getUniformLoacation(const std :: string& name );
};

