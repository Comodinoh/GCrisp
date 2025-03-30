
//type vertex

#version 330 core

in vec3 a_Position;
in vec4 a_Color;
in vec2 a_TexCoord;
in float a_TexID;

out vec4 color;
out vec2 texCoord;
flat out float texID;

uniform mat4 u_ViewProj;

void main()
{
    color = a_Color;
    texCoord = a_TexCoord;
    texID = a_TexID;
        
    gl_Position = u_ViewProj * vec4(a_Position, 1.0f);
}

//type fragment

#version 330 core

in vec4 color;
in vec2 texCoord;
flat in float texID;

out vec4 fragColor;

uniform sampler2D[32] u_Textures;

void main()
{
    int texIDInt = int(texID);
    fragColor = texture(u_Textures[texIDInt], texCoord) * color;
}