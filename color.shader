#vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoordinates;

uniform mat4 comboMatrix;

out vec2 tex;

void main()
{
    gl_Position = comboMatrix * vec4(position, 1.0);
    tex = texCoordinates;
}

#fragment
#version 330 core

uniform sampler2D s;

in vec2 tex;
out vec4 color;

void main()
{
    color = vec4(1.0, 0.0, 0.0, 1.0);
}

