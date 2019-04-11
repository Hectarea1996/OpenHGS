
#include "ShaderTexture.h"
#include "../hgsUniformBuffer/UboLuzDireccion.h"
#include "../hgsUniformBuffer/UboLuzPunto.h"
#include "../hgsUniformBuffer/UboLuzLinterna.h"
#include "../hgsUniformBuffer/UboView.h"
#include "../hgsUniformBuffer/UboViewPos.h"
#include "../hgsUniformBuffer/UboProjection.h"
#include "../hgsVideo/mesh.h"
#include "../hgsVideo/model.h"
#include <iostream>
using namespace std;
using namespace glm;
using namespace hgs;


static void deleteBuffer(unsigned int * buffer){
    glDeleteBuffers(1,buffer);
    delete buffer;
}

static void deleteVertexArray(unsigned int * vertexArray){
    glDeleteVertexArrays(1,vertexArray);
    delete vertexArray;
}


ShaderTexture::ShaderTexture()
: ShaderProgram("./Shaders/textureShader/textureShader.vs","./Shaders/textureShader/textureShader.fs"){

    glUseProgram(*this->idProgram);

    glUniform1i(glGetUniformLocation(*this->idProgram,"material.ambient"),0);
    glUniform1i(glGetUniformLocation(*this->idProgram,"material.diffuse"),1);
    glUniform1i(glGetUniformLocation(*this->idProgram,"material.specular"),2);

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

Vao ShaderTexture::createVao(const VaoInfo& vaoInfo) const{

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
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    shared_ptr<unsigned> ptrVBO(new unsigned(vbo),deleteBuffer);
    shared_ptr<unsigned> ptrEBO(new unsigned(ebo),deleteBuffer);
    shared_ptr<unsigned> ptrVAO(new unsigned(vao),deleteVertexArray);

    return Vao(*this,move(ptrVBO),move(ptrEBO),move(ptrVAO),vaoInfo.indices.size());

}
