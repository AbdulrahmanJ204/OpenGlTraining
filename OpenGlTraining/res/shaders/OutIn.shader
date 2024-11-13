#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 inColor;

out vec4 vertexColor;
// trying to do some comments here
/* another
comment*/
void main()
{
    gl_Position = position;
    vertexColor = inColor;
};

#shader fragment

#version 330 core
in vec4 vertexColor;
out vec4 color;

void main()
{
    color = vertexColor;
};
