#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
//layout(location = 1) in vec4 color;
layout(location = 1) in vec2 texCoordIn;

uniform mat4 u_MVP;
out vec2 v_TexCoord; // v_ for varying

void main() {
    gl_Position = u_MVP *vec4(position , 1.0);
    v_TexCoord = texCoordIn;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
};
