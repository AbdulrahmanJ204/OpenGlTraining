#include "Texture.h"
#include "stb_image/stb_image.h"
Texture::Texture(const std::string& filepath)
	: m_RendererID(0), m_FilePath(filepath), m_LocalBuffer(0), m_Width(0), m_Height(0), m_BPP(0)
{
	// loading image :
	stbi_set_flip_vertically_on_load(1); // if you see your texture upside down , try with this

	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4); // 4 is how many desired channel , we need rgba so 4.



	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // just do it like this for now , search for it later
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // just do it like this for now , search for it later
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // wrapS , wrapT , for x and y i guess

	// send data to opengl
	// check docs.gl 
	//                                                                            bits per channel / or bytes idk
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	Unbind();

	if (m_LocalBuffer) // if it has data
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot ) const
{
	// specify the slot;
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
