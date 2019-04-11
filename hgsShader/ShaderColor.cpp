
#include "shaderColor.h"
#include "../hgsVideo/luzDireccion.h"
#include "../hgsVideo/luzPunto.h"
#include "../hgsVideo/luzLinterna.h"
#include "../hgsVideo/model.h"
#include "../hgsUniformBuffer/UboProjection.h"
#include "../hgsUniformBuffer/UboView.h"
#include "../hgsUniformBuffer/UboViewPos.h"
#include "../hgsUniformBuffer/UboLuzDireccion.h"
#include "../hgsUniformBuffer/UboLuzPunto.h"
#include "../hgsUniformBuffer/UboLuzLinterna.h"
#include <iostream>
using namespace std;
using namespace hgs;
using namespace glm;

static void deleteBuffer(unsigned int * buffer){
    glDeleteBuffers(1,buffer);
    delete buffer;
}

static void deleteVertexArray(unsigned int * vertexArray){
    glDeleteVertexArrays(1,vertexArray);
    delete vertexArray;
}

ShaderColor::ShaderColor()
: ShaderProgram("./Shaders/colorShader/colorShader.vs","./Shaders/colorShader/colorShader.fs"){

    glUseProgram(*this->idProgram);

    //Textures
    glUniform1i(glGetUniformLocation(*this->idProgram,"skybox"),0);
    glUniform1i(glGetUniformLocation(*this->idProgram,"shadowDirMap"),1);
    glUniform1i(glGetUniformLocation(*this->idProgram,"shadowPunMap"),2);



    UboView& uboView= UboView::getInstancia();
    unsigned int view_index = glGetUniformBlockIndex(*this->idProgram, "ViewMatrix");
    if (view_index==GL_INVALID_INDEX){
        cout << "View index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,view_index,uboView.getBindPoint());

    UboViewPos& uboViewPos= UboViewPos::getInstancia();
    unsigned int viewPos_index = glGetUniformBlockIndex(*this->idProgram, "ViewPosition");
    if (viewPos_index==GL_INVALID_INDEX){
        cout << "ViewPos index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,viewPos_index,uboViewPos.getBindPoint());

    UboProjection& uboProjection= UboProjection::getInstancia();
    unsigned int projection_index = glGetUniformBlockIndex(*this->idProgram, "ProjectionMatrix");
    if (projection_index==GL_INVALID_INDEX){
        cout << "Projection index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,projection_index,uboProjection.getBindPoint());

    UboLuzDireccion& uboLuzDir= UboLuzDireccion::getInstancia();
    unsigned int luzdir_index= glGetUniformBlockIndex(*this->idProgram,"LucesDireccion");
    if (luzdir_index==GL_INVALID_INDEX){
        cout << "Direccion index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,luzdir_index,uboLuzDir.getBindPoint());

    UboLuzPunto& uboLuzPunto= UboLuzPunto::getInstancia();
    unsigned int luzpun_index= glGetUniformBlockIndex(*this->idProgram, "LucesPunto");
    if (luzpun_index==GL_INVALID_INDEX){
        cout << "Punto index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,luzpun_index,uboLuzPunto.getBindPoint());

    UboLuzLinterna& uboLuzLin= UboLuzLinterna::getInstancia();
    unsigned int luzlin_index= glGetUniformBlockIndex(*this->idProgram, "LucesLinterna");
    if (luzlin_index==GL_INVALID_INDEX){
        cout << "Linterna index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,luzlin_index,uboLuzLin.getBindPoint());



}

Vao ShaderColor::createVao(const VaoInfo& vaoInfo) const{

    unsigned int vbo;
    unsigned int ebo;
    unsigned int vao;

    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
    glGenVertexArrays(1,&vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vaoInfo.vertices.size()*sizeof(Vertex),vaoInfo.vertices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vaoInfo.indices.size()*sizeof(unsigned),vaoInfo.indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,normal));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    shared_ptr<unsigned> ptrVBO(new unsigned(vbo),deleteBuffer);
    shared_ptr<unsigned> ptrEBO(new unsigned(ebo),deleteBuffer);
    shared_ptr<unsigned> ptrVAO(new unsigned(vao),deleteVertexArray);

    return Vao(*this,move(ptrVBO),move(ptrEBO),move(ptrVAO),vaoInfo.indices.size());

}

//Model ShaderColor::createModel(const std::vector<hgs::MeshInfo>& vm) const{
//
//    vector<Mesh> vectorMesh;
//    for (const MeshInfo& m : vm){
//        vectorMesh.push_back(this->createMesh(m));
//    }
//    return Model(move(vectorMesh));
//
//}


//#define INDICE_CAMBIO   7
//
//inline static void cambiarIndice1(string& palabra, unsigned int indice){
//    char numero= indice+48;
//    palabra[INDICE_CAMBIO]= numero;
//}
//
//inline static void cambiarIndice2(string& palabra, unsigned int indice){
//    char decenas= (indice/10)+48;
//    char unidades= (indice%10)+48;
//    palabra[INDICE_CAMBIO]= decenas;
//    palabra[INDICE_CAMBIO+1]= unidades;
//}
//
//static string * inicializarDireccion1(){
//    static string atributos1[5];
//    atributos1[0]= "luzDir[0].direccion";
//    atributos1[1]= "luzDir[0].ambient";
//    atributos1[2]= "luzDir[0].diffuse";
//    atributos1[3]= "luzDir[0].specular";
//    atributos1[4]= "dirEnc[0]";
//    return atributos1;
//}
//
//static string * inicializarDireccion2(){
//    static string atributos2[5];
//    atributos2[0]= "luzDir[00].direccion";
//    atributos2[1]= "luzDir[00].ambient";
//    atributos2[2]= "luzDir[00].diffuse";
//    atributos2[3]= "luzDir[00].specular";
//    atributos2[4]= "dirEnc[00]";
//    return atributos2;
//}
//
//
////void ShaderColor::setLuzDireccion(const LuzDireccion& luz, unsigned int indice) const{
////
////    // 1 cifra
////    static string * atributos1= inicializarDireccion1();
////
////    // 2 cifras
////    static string * atributos2= inicializarDireccion2();
////
////    if (indice<10){
////        for (int i=0; i<4; i++)
////            cambiarIndice1(atributos1[i],indice);
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[0].c_str()),1,value_ptr(luz.direccion));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[1].c_str()),1,value_ptr(luz.ambient));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[2].c_str()),1,value_ptr(luz.diffuse));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[3].c_str()),1,value_ptr(luz.specular));
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributos1[4].c_str()),1);
////    }
////    else if (indice<100){
////        for (int i=0; i<4; i++)
////            cambiarIndice2(atributos2[i],indice);
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[0].c_str()),1,value_ptr(luz.direccion));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[1].c_str()),1,value_ptr(luz.ambient));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[2].c_str()),1,value_ptr(luz.diffuse));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[3].c_str()),1,value_ptr(luz.specular));
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributos2[4].c_str()),1);
////    }
////
////}
//
//
//static string * inicializarPunto1(){
//    static string atributos1[8];
//    atributos1[0]= "luzPun[0].position";
//    atributos1[1]= "luzPun[0].ambient";
//    atributos1[2]= "luzPun[0].diffuse";
//    atributos1[3]= "luzPun[0].specular";
//    atributos1[4]= "luzPun[0].constant";
//    atributos1[5]= "luzPun[0].linear";
//    atributos1[6]= "luzPun[0].quadratic";
//    atributos1[7]= "punEnc[0]";
//    return atributos1;
//}
//
//static string * inicializarPunto2(){
//    static string atributos2[8];
//    atributos2[0]= "luzPun[00].position";
//    atributos2[1]= "luzPun[00].ambient";
//    atributos2[2]= "luzPun[00].diffuse";
//    atributos2[3]= "luzPun[00].specular";
//    atributos2[4]= "luzPun[00].constant";
//    atributos2[5]= "luzPun[00].linear";
//    atributos2[6]= "luzPun[00].quadratic";
//    atributos2[7]= "punEnc[00]";
//    return atributos2;
//}
//
////void ShaderColor::setLuzPunto(const LuzPunto& luz, unsigned int indice) const{
////
////    // 1 cifra
////    static string * atributos1= inicializarPunto1();
////
////    // 2 cifras
////    static string * atributos2= inicializarPunto2();
////
////    if (indice<10){
////        for (int i=0; i<7; i++)
////            cambiarIndice1(atributos1[i],indice);
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[0].c_str()),1,value_ptr(luz.position));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[1].c_str()),1,value_ptr(luz.ambient));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[2].c_str()),1,value_ptr(luz.diffuse));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[3].c_str()),1,value_ptr(luz.specular));
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[4].c_str()),luz.aten.constant);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[5].c_str()),luz.aten.linear);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[6].c_str()),luz.aten.quadratic);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributos1[7].c_str()),1);
////    }
////    else if (indice<100){
////        for (int i=0; i<7; i++)
////            cambiarIndice2(atributos2[i],indice);
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[0].c_str()),1,value_ptr(luz.position));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[1].c_str()),1,value_ptr(luz.ambient));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[2].c_str()),1,value_ptr(luz.diffuse));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[3].c_str()),1,value_ptr(luz.specular));
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[4].c_str()),luz.aten.constant);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[5].c_str()),luz.aten.linear);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[6].c_str()),luz.aten.quadratic);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributos2[7].c_str()),1);
////    }
////
////}
//
//static string * inicializarLinterna1(){
//    static string atributos1[11];
//    atributos1[0]= "luzLin[0].position";
//    atributos1[1]= "luzLin[0].direccion";
//    atributos1[2]= "luzLin[0].ambient";
//    atributos1[3]= "luzLin[0].diffuse";
//    atributos1[4]= "luzLin[0].specular";
//    atributos1[5]= "luzLin[0].constant";
//    atributos1[6]= "luzLin[0].linear";
//    atributos1[7]= "luzLin[0].quadratic";
//    atributos1[8]= "luzLin[0].phiIn";
//    atributos1[9]= "luzLin[0].phiOut";
//    atributos1[10]= "linEnc[0]";
//    return atributos1;
//}
//
//static string * inicializarLinterna2(){
//    static string atributos2[11];
//    atributos2[0]= "luzLin[00].position";
//    atributos2[1]= "luzLin[00].direccion";
//    atributos2[2]= "luzLin[00].ambient";
//    atributos2[3]= "luzLin[00].diffuse";
//    atributos2[4]= "luzLin[00].specular";
//    atributos2[5]= "luzLin[00].constant";
//    atributos2[6]= "luzLin[00].linear";
//    atributos2[7]= "luzLin[00].quadratic";
//    atributos2[8]= "luzLin[00].phiIn";
//    atributos2[9]= "luzLin[00].phiOut";
//    atributos2[10]= "linEnc[00]";
//    return atributos2;
//}
//
//
////void ShaderColor::setLuzLinterna(const LuzLinterna& luz, unsigned int indice) const{
////
////    // 1 cifra
////    static string * atributos1= inicializarLinterna1();
////
////    // 2 cifras
////    static string * atributos2= inicializarLinterna2();
////
////    if (indice<10){
////        for (int i=0; i<10; i++)
////            cambiarIndice1(atributos1[i],indice);
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[0].c_str()),1,value_ptr(luz.position));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[1].c_str()),1,value_ptr(luz.direccion));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[2].c_str()),1,value_ptr(luz.ambient));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[3].c_str()),1,value_ptr(luz.diffuse));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos1[4].c_str()),1,value_ptr(luz.specular));
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[5].c_str()),luz.aten.constant);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[6].c_str()),luz.aten.linear);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[7].c_str()),luz.aten.quadratic);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[8].c_str()),cos(radians(luz.phiIn)));
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos1[9].c_str()),cos(radians(luz.phiOut)));
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributos1[10].c_str()),1);
////    }
////    else if (indice<100){
////        for (int i=0; i<10; i++)
////            cambiarIndice2(atributos2[i],indice);
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[0].c_str()),1,value_ptr(luz.position));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[1].c_str()),1,value_ptr(luz.direccion));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[2].c_str()),1,value_ptr(luz.ambient));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[3].c_str()),1,value_ptr(luz.diffuse));
////        glUniform3fv(glGetUniformLocation(*this->idProgram,atributos2[4].c_str()),1,value_ptr(luz.specular));
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[5].c_str()),luz.aten.constant);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[6].c_str()),luz.aten.linear);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[7].c_str()),luz.aten.quadratic);
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[8].c_str()),cos(radians(luz.phiIn)));
////        glUniform1f(glGetUniformLocation(*this->idProgram,atributos2[9].c_str()),cos(radians(luz.phiOut)));
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributos2[10].c_str()),1);
////    }
////
////}
////
////void ShaderColor::apagarLuzDireccion(unsigned int indice) const{
////
////    static string atributo1= "dirEnc[0]";
////    static string atributo2= "dirEnc[00]";
////
////    if (indice<10){
////        cambiarIndice1(atributo1,indice);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributo1.c_str()),0);
////    }
////    else if (indice<100){
////        cambiarIndice2(atributo2,indice);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributo2.c_str()),0);
////    }
////
////
////}
////
////void ShaderColor::apagarLuzPunto(unsigned int indice) const{
////
////    static string atributo1= "punEnc[0]";
////    static string atributo2= "punEnc[00]";
////
////    if (indice<10){
////        cambiarIndice1(atributo1,indice);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributo1.c_str()),0);
////    }
////    else if (indice<100){
////        cambiarIndice2(atributo2,indice);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributo2.c_str()),0);
////    }
////
////}
////void ShaderColor::apagarLuzLinterna(unsigned int indice) const{
////
////    static string atributo1= "linEnc[0]";
////    static string atributo2= "linEnc[00]";
////
////    if (indice<10){
////        cambiarIndice1(atributo1,indice);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributo1.c_str()),0);
////    }
////    else if (indice<100){
////        cambiarIndice2(atributo2,indice);
////        glUniform1i(glGetUniformLocation(*this->idProgram,atributo2.c_str()),0);
////    }
////
////}
