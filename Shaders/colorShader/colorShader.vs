
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
    vec4 fPosLight;
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
uniform mat4 lightSpaceMatrix;

void main(){

    gl_Position = projection*view*model*vec4(position,1.0);

    vs_out.fPos= vec3(model*vec4(position,1));
    vs_out.normalVec= normalMatrix*normal;
    vs_out.viewPos= viewPosition;
    vs_out.fPosLight = lightSpaceMatrix*vec4(vs_out.fPos,1.0);

}
