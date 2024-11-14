#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 inColor;

out vec4 vertexColor;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP *position;
    vertexColor = inColor;
};
#shader fragment

#version 330 core
// make sure that "in vec4 "name is the same as  "out vec4" in Vertex Shader
in vec4 vertexColor;
out vec4 color;

void main()
{
    color = vertexColor;
};
