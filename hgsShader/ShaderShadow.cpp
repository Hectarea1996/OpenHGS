
#include "ShaderShadow.h"
#include "../hgsVideo/Vao.h"

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

Vao ShaderShadow::createVao(const VaoInfo& vaoInfo) const{

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

    glBindVertexArray(0);

    shared_ptr<unsigned> ptrVBO(new unsigned(vbo),deleteBuffer);
    shared_ptr<unsigned> ptrEBO(new unsigned(ebo),deleteBuffer);
    shared_ptr<unsigned> ptrVAO(new unsigned(vao),deleteVertexArray);

    return Vao(*this,move(ptrVBO),move(ptrEBO),move(ptrVAO),vaoInfo.indices.size());

}
