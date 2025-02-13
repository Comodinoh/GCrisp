
//type vertex

#version 330 core

in vec3 a_Position;
in vec2 a_TexCoord;

out vec2 texCoord;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0);
    texCoord = a_TexCoord;
}

//type fragment
#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    fragColor = texture(u_Texture, texCoord) * u_Color;
}