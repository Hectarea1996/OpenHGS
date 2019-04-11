
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 cordTexture;

out INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
    vec2 texCord;
}vs_out;

layout (std140) uniform ProjectionMatrix{
    mat4 projection;
};

layout (std140) uniform ViewMatrix{
    mat4 view;
};

layout (std140) uniform ViewPosition{
    vec3 viewPosition;
};

uniform mat4 model;
uniform mat3 normalMatrix;

void main(){

    gl_Position = projection*view*model*vec4(position,1.0);

    vs_out.fPos= vec3(model*vec4(position,1));
    vs_out.normalVec= normalMatrix*normal;
    vs_out.viewPos= viewPosition;
    vs_out.texCord = cordTexture;

}
