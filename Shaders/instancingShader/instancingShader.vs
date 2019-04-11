
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
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

uniform mat4 modelPF;
uniform mat4 model;
uniform mat3 normalMatrix;
uniform mat3 normalMatrixPF;
uniform float offset;
uniform int totalModels;


float getParametro(){
    float idInstance= gl_InstanceID;
    float param= (idInstance/(totalModels-1))+offset;
    param= mod(param,1.0);
    return param;
}


vec4 funcionParametro(){
    float t= 6.283185307*getParametro();
    float radio= 10.0;
    float m= 10;
    float n= 1;
    return vec4(radio*cos(m*t)*cos(n*t),radio*sin(m*t)*cos(n*t),radio*sin(n*t),0.0);
}


vec4 getInstancedVec(){

    vec4 traslacion= funcionParametro();
    return traslacion;

}


void main(){

    vec4 instancedPosition= getInstancedVec();
    gl_Position = projection*view*(instancedPosition+model*vec4(position,1.0));

    vs_out.fPos= vec3(model*vec4(position,1.0)+instancedPosition);
    vs_out.normalVec= normalMatrix*normal;
    vs_out.viewPos= viewPosition;

}
