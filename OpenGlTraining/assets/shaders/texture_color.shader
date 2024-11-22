#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoordIn;

uniform mat4 u_MVP; 

out vec4 v_Color;
out vec2 v_TexCoord; // v_ for varying

void main() {
    gl_Position = u_MVP *vec4(position , 1.0);
    v_TexCoord = texCoordIn;
    v_Color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform float u_Mix;

void main() {
    //vec4 texColor = texture(u_Texture1, v_TexCoord);
    vec4 texColor = 
    mix(texture(u_Texture1, v_TexCoord) , 
    texture(u_Texture2, v_TexCoord) , u_Mix);
    color = texColor;
    //color = texColor * v_Color;
};
