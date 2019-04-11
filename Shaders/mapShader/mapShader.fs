#version 330 core

in vec2 quadCoords;
out vec4 FragColor;

uniform sampler2D map;


void main(){

    FragColor= texture(map,quadCoords);

}
