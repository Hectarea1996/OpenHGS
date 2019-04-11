
#include "UniformBuffer.h"
#include "../OpenHGS.h"
#include <cassert>

static void deleteUniformBuffer(unsigned * ubo){
    glDeleteBuffers(1,ubo);
    delete ubo;
}

UniformBuffer::UniformBuffer(unsigned int bytes, unsigned int bindPoint)
: ubo(new unsigned(0),deleteUniformBuffer), bindPoint(bindPoint){

    glGenBuffers(1,this->ubo.get());
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferData(GL_UNIFORM_BUFFER,bytes,nullptr,GL_STATIC_DRAW);

    glBindBufferRange(GL_UNIFORM_BUFFER,bindPoint,*this->ubo,0,bytes);

    glBindBuffer(GL_UNIFORM_BUFFER,0);

}

//void UniformBuffer::cargar(){
//
//    assert(!this->cargado);
//
//    glGenBuffers(1,this->ubo.get());
//    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
//    glBufferData(GL_UNIFORM_BUFFER,bytes,nullptr,GL_STATIC_DRAW);
//
//    glBindBufferRange(GL_UNIFORM_BUFFER,bindPoint,*this->ubo,0,this->bytes);
//
//    glBindBuffer(GL_UNIFORM_BUFFER,0);
//
//    this->cargado= true;
//
//}
