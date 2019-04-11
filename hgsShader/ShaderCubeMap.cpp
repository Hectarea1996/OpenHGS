#include "ShaderCubeMap.h"
#include "../hgsUniformBuffer/UboView.h"
#include "../hgsUniformBuffer/UboProjection.h"
#include "../hgsVideo/Vao.h"
using namespace hgs;
using namespace std;

static void deleteBuffer(unsigned int * buffer){
    glDeleteBuffers(1,buffer);
    delete buffer;
}

static void deleteVertexArray(unsigned int * vertexArray){
    glDeleteVertexArrays(1,vertexArray);
    delete vertexArray;
}


ShaderCubeMap::ShaderCubeMap()
: ShaderProgram("./Shaders/cubeMapShader/cubeMapShader.vs","./Shaders/cubeMapShader/cubeMapShader.fs"){

    glUseProgram(*this->idProgram);
    glUniform1i(glGetUniformLocation(*this->idProgram,"cubeMap"),0);

    UboView& uboView= UboView::getInstancia();
    unsigned int view_index = glGetUniformBlockIndex(*this->idProgram, "ViewMatrix");
    if (view_index==GL_INVALID_INDEX){
        cout << "View index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,view_index,uboView.getBindPoint());

    UboProjection& uboProjection= UboProjection::getInstancia();
    unsigned int projection_index = glGetUniformBlockIndex(*this->idProgram, "ProjectionMatrix");
    if (projection_index==GL_INVALID_INDEX){
        cout << "Projection index invalid" << endl;
        exit(EXIT_FAILURE);
    }
    glUniformBlockBinding(*this->idProgram,projection_index,uboProjection.getBindPoint());

}


Vao ShaderCubeMap::createVao(const VaoInfo& vaoInfo) const{

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
