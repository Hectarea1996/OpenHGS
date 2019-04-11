
#include "ProjectionMatrix.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace hgs;
using namespace glm;

#define HGS_MODO_PERSPECTIVA    0
#define HGS_MODO_ORTOGONAL      1


mat4 ProjectionMatrix::getProjectionMatrix(){
    assert(this->inicializado);
    switch (this->modo){
        case HGS_MODO_PERSPECTIVA:
            return perspective(this->fov,this->right/this->top,this->_near,this->_far);
        case HGS_MODO_ORTOGONAL:
            return ortho(this->left,this->right,this->bottom,this->top,this->_near,this->_far);
    }
    exit(EXIT_FAILURE);
    return mat4(1);
}

void ProjectionMatrix::setPerspective(float ancho, float alto, float fov, float _near, float _far){
    this->left= 0;
    this->right= ancho;
    this->bottom= 0;
    this->top= alto;
    this->fov= fov;
    this->_near= _near;
    this->_far= _far;

    this->modo= HGS_MODO_PERSPECTIVA;
    this->inicializado= true;
}

void ProjectionMatrix::setOrthogonal(float left, float right, float bottom, float top, float _near, float _far){
    this->left= left;
    this->right= right;
    this->bottom= bottom;
    this->top= top;
    this->_near= _near;
    this->_far= _far;

    this->modo= HGS_MODO_ORTOGONAL;
    this->inicializado= true;
}
