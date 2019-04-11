#version 330 core

in vec2 quadCoords;
out vec4 FragColor;

uniform sampler2D depthMap;

//float near= 0.1;
//float far= 100.0;

//float LinearizeDepth(float depth) {
//
//    float z = depth * 2.0 - 1.0;
//    // back to NDC
//    return (2.0 * near * far) / (far + near - z * (far - near));
//}


void main(){

    float depth= texture(depthMap,quadCoords).r;
    FragColor= vec4(vec3(depth),1.0);

    //vec4 depth= texture(depthMap,quadCoords);
    //FragColor= depth;


}
