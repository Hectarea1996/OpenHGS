
#include "Triangulo.h"
#include "../hgsVideo/VaoInfo.h"
#include <glad/glad.h>
using namespace glm;
using namespace hgs;
using namespace std;


VaoInfo Triangulo::getVaoInfo(){

    Vertex a(vec3(-0.8660,-0.5,0),vec3(0,0,1),vec2(0,0));
    Vertex b(vec3(0.8660,-0.5,0),vec3(0,0,1),vec2(1,0));
    Vertex c(vec3(0,1,0),vec3(0,0,1),vec2(0.5,1));
    vector<Vertex> vMesh({a,b,c});

    vector<unsigned> indices({0,1,2});

    return VaoInfo(move(vMesh),move(indices));

}

VaoInfo Triangulo::getVaoInfo(const glm::vec2& t1, const glm::vec2& t2, const glm::vec2& t3){

    Vertex a(vec3(-0.8660,-0.5,0),vec3(0,0,1),t1);
    Vertex b(vec3(0.8660,-0.5,0),vec3(0,0,1),t2);
    Vertex c(vec3(0,1,0),vec3(0,0,1),t3);
    vector<Vertex> vMesh({a,b,c});

    vector<unsigned> indices({0,1,2});

    return VaoInfo(move(vMesh),move(indices));

}

