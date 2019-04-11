
#include "ModelMatrix.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace hgs;

mat4 ModelMatrix::getTraslacion(){

    if (this->control.cambioTras){
        this->control.tras= translate(mat4(1),this->posicion);
        this->control.cambioMatrix= true;
    }

    return this->control.tras;

}


mat4 ModelMatrix::getOrientacion(){

    if (this->control.cambioX){
        this->control.rotX= rotate(mat4(1),this->pitch,vec3(1,0,0));
        this->control.cambioOri= true;
    }
    if (this->control.cambioY){
        this->control.rotY= rotate(mat4(1),this->yaw,vec3(0,1,0));
        this->control.cambioOri= true;
    }
    if (this->control.cambioZ){
        this->control.rotZ= rotate(mat4(1),this->roll,vec3(0,0,1));
        this->control.cambioOri= true;
    }
    if (this->control.cambioOri){
        this->control.ori= control.rotY*control.rotX*control.rotZ;
        this->control.cambioMatrix= true;
    }

    return this->control.ori;

}

mat3 ModelMatrix::getNormalMatrix(){
    return (mat3)this->getOrientacion();
}

mat4 ModelMatrix::getModelMatrix(){

    if (this->control.cambioX){
        this->control.rotX= rotate(mat4(1),this->pitch,vec3(1,0,0));
        this->control.cambioOri= true;
    }
    if (this->control.cambioY){
        this->control.rotY= rotate(mat4(1),this->yaw,vec3(0,1,0));
        this->control.cambioOri= true;
    }
    if (this->control.cambioZ){
        this->control.rotZ= rotate(mat4(1),this->roll,vec3(0,0,1));
        this->control.cambioOri= true;
    }
    if (this->control.cambioTras){
        this->control.tras= translate(mat4(1),this->posicion);
        this->control.cambioMatrix= true;
    }
    if (this->control.cambioScale){
        this->control.scale= glm::scale(mat4(1),this->scale);
        this->control.cambioMatrix= true;
    }
    if (this->control.cambioOri){
        this->control.ori= control.rotY*control.rotX*control.rotZ;
        this->control.cambioMatrix= true;
    }
    if (this->control.cambioMatrix){
        this->control.matrix= control.tras*control.ori*this->control.scale;
        this->control.setFalse();
    }

    return this->control.matrix;

}
