#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texcoord;
layout (location = 3) in mat4 model;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 ViewPos;

uniform mat4 view;
uniform mat4 projection;


void main()
{
    TexCoord = texcoord.xy;
    gl_Position = projection * view * model * vec4(position, 1.0);

    Normal = mat3(transpose(inverse(model))) * normal;
    FragPos = vec3(model * vec4(position, 1.0));
    ViewPos = position;
}