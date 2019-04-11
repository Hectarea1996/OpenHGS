
#include "Rectangulo.h"
#include <vector>
#include "../OpenHGS.h"
#include "../hgsVideo/VaoInfo.h"
using namespace glm;
using namespace hgs;
using namespace std;

VaoInfo Rectangulo::getVaoInfo(){

    Vertex a(vec3(-1,-1,0),vec3(0,0,1),vec2(0,0));
    Vertex b(vec3(1,-1,0),vec3(0,0,1),vec2(1,0));
    Vertex c(vec3(1,1,0),vec3(0,0,1),vec2(1,1));
    Vertex d(vec3(-1,1,0),vec3(0,0,1),vec2(0,1));
    vector<Vertex> vr({a,b,c,d});

    vector<unsigned> indices({0,1,3,
                              3,1,2});

    return VaoInfo(move(vr),move(indices));

}

VaoInfo Rectangulo::getVaoInfo(const std::array<glm::vec2,4>& texCoords){

    Vertex a(vec3(-1,-1,0),vec3(0,0,1),texCoords[0]);
    Vertex b(vec3(1,-1,0),vec3(0,0,1),texCoords[1]);
    Vertex c(vec3(1,1,0),vec3(0,0,1),texCoords[2]);
    Vertex d(vec3(-1,1,0),vec3(0,0,1),texCoords[3]);
    vector<Vertex> vr({a,b,c,d});

    vector<unsigned> indices({0,1,3,
                              3,1,2});

    return VaoInfo(move(vr),move(indices));

}
