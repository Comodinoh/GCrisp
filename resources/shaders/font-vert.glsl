#version 330

in vec4 vertexColor;
in vec3 vertexPosition;
in vec2 vertexTexCoord;

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat4 mvp;
uniform float time;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
