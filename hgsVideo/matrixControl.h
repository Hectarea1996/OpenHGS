#ifndef MATRIXCONTROL_H_INCLUDED
#define MATRIXCONTROL_H_INCLUDED


#include <glm/glm.hpp>

namespace hgs{

struct MatrixControl{

    bool cambioX;
    bool cambioY;
    bool cambioZ;
    bool cambioTras;
    bool cambioOri;
    bool cambioMatrix;
    bool cambioScale;
    glm::mat4 rotX;
    glm::mat4 rotY;
    glm::mat4 rotZ;
    glm::mat4 scale;
    glm::mat4 tras;
    glm::mat4 ori;
    glm::mat4 matrix;

    MatrixControl(): cambioX(true), cambioY(true), cambioZ(true), cambioTras(true), cambioOri(true), cambioMatrix(true),
                        rotX(1), rotY(1), rotZ(1), matrix(1){}

    void setFalse(){
        this->cambioX= false;
        this->cambioY= false;
        this->cambioZ= false;
        this->cambioScale= false;
        this->cambioTras= false;
        this->cambioMatrix= false;
        this->cambioOri= false;
    }

    void setTrue(){
        this->cambioX= true;
        this->cambioY= true;
        this->cambioZ= true;
        this->cambioScale= true;
        this->cambioTras= true;
        this->cambioMatrix= true;
        this->cambioOri= true;
    }

};


}

#endif // MATRIXCONTROL_H_INCLUDED
