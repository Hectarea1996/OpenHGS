
#include "ShaderShadowCubeMap.h"
#include "../hgsVideo/Vao.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
using namespace hgs;
using namespace glm;
using namespace std;

static void deleteBuffer(unsigned int * buffer){
    glDeleteBuffers(1,buffer);
    delete buffer;
}

static void deleteVertexArray(unsigned int * vertexArray){
    glDeleteVertexArrays(1,vertexArray);
    delete vertexArray;
}

Vao ShaderShadowCubeMap::createVao(const VaoInfo& vaoInfo) const{

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


void ShaderShadowCubeMap::setLightPosition(glm::vec3 lightPosition) const{

    static std::array<glm::mat4,6> shadowTransforms= {glm::lookAt(lightPosition, lightPosition + glm::vec3( 1.0, 0.0, 0.0), glm:: vec3(0.0,-1.0, 0.0)),
                                                      glm::lookAt(lightPosition, lightPosition + glm::vec3(-1.0, 0.0, 0.0), glm:: vec3(0.0,-1.0, 0.0)),
                                                      glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0, 1.0, 0.0), glm:: vec3(0.0, 0.0, 1.0)),
                                                      glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0,-1.0, 0.0), glm:: vec3(0.0, 0.0,-1.0)),
                                                      glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0, 0.0, 1.0), glm:: vec3(0.0,-1.0, 0.0)),
                                                      glm::lookAt(lightPosition, lightPosition + glm::vec3( 0.0, 0.0,-1.0), glm:: vec3(0.0,-1.0, 0.0))};

    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"viewShadow[0]"),1,GL_FALSE,value_ptr(shadowTransforms[0]));
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"viewShadow[1]"),1,GL_FALSE,value_ptr(shadowTransforms[1]));
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"viewShadow[2]"),1,GL_FALSE,value_ptr(shadowTransforms[2]));
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"viewShadow[3]"),1,GL_FALSE,value_ptr(shadowTransforms[3]));
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"viewShadow[4]"),1,GL_FALSE,value_ptr(shadowTransforms[4]));
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"viewShadow[5]"),1,GL_FALSE,value_ptr(shadowTransforms[5]));

    glUniform3fv(glGetUniformLocation(*this->idProgram,"lightPos"),1,value_ptr(lightPosition));

}
