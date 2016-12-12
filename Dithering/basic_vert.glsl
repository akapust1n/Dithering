#version 330 core

in vec2 vertexPosition;
in vec2 textureCoordinates;

uniform mat4 viewProjectionMatrix;

out vec2 v_textureCoordinates;

void main()
{
    v_textureCoordinates = vec2(textureCoordinates);
    gl_Position = viewProjectionMatrix * vec4(vertexPosition, 0.0, 1.0);
}
