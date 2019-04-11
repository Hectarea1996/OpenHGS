
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
}gs_in[];

out INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
}gs_out;

vec3 GetNormal() {
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main(){

    for (int i=0; i<3; i++){
        gl_Position= gl_in[i].gl_Position+vec4(GetNormal(),0.0)*0.3;
        gs_out.fPos= gs_in[i].fPos;
        gs_out.normalVec= gs_in[i].normalVec;
        gs_out.viewPos= gs_in[i].viewPos;
        EmitVertex();
    }
    EndPrimitive();

}
