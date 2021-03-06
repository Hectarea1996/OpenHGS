
#include "cubo.h"
#include "../hgsVideo/VaoInfo.h"
#include <vector>
using namespace hgs;
using namespace std;

VaoInfo Cubo::getVaoInfo(){

    vector<Vertex> vertices{{{-1,-1,1},     {0,0,1},      {0,0}},    //Posterior
                           {{1,-1,1},      {0,0,1},      {1,0}},
                           {{1,1,1},       {0,0,1},      {1,1}},
                           {{-1,1,1},      {0,0,1},      {0,1}},
                           {{1,-1,1},      {1,0,0},      {0,0}},    //Derecha
                           {{1,-1,-1},     {1,0,0},      {1,0}},
                           {{1,1,-1},      {1,0,0},      {1,1}},
                           {{1,1,1},       {1,0,0},      {0,1}},
                           {{-1,-1,-1},    {-1,0,0},     {0,0}},    //Izquierda
                           {{-1,-1,1},     {-1,0,0},     {1,0}},
                           {{-1,1,1},      {-1,0,0},     {1,1}},
                           {{-1,1,-1},     {-1,0,0},     {0,1}},
                           {{1,-1,-1},     {0,0,-1},     {0,0}},    //Anterior
                           {{-1,-1,-1},    {0,0,-1},     {1,0}},
                           {{-1,1,-1},     {0,0,-1},     {1,1}},
                           {{1,1,-1},      {0,0,-1},     {0,1}},
                           {{-1,-1,-1},    {0,-1,0},     {0,0}},    //Abajo
                           {{1,-1,-1},     {0,-1,0},     {1,0}},
                           {{1,-1,1},      {0,-1,0},     {1,1}},
                           {{-1,-1,1},     {0,-1,0},     {0,1}},
                           {{-1,1,1},      {0,1,0},      {0,0}},    //Arriba
                           {{1,1,1},       {0,1,0},      {1,0}},
                           {{1,1,-1},      {0,1,0},      {1,1}},
                           {{-1,1,-1},     {0,1,0},      {0,1}}};


    vector<unsigned int> indices{0,1,2,
                                 2,3,0,
                                 4,5,6,
                                 6,7,4,
                                 8,9,10,
                                 10,11,8,
                                 12,13,14,
                                 14,15,12,
                                 16,17,18,
                                 18,19,16,
                                 20,21,22,
                                 22,23,20};

    return VaoInfo(move(vertices),move(indices));

}

