#ifndef MODELMATRIX_H_INCLUDED
#define MODELMATRIX_H_INCLUDED


#include "matrixControl.h"
#include <glm/glm.hpp>

namespace hgs{

class ModelMatrix{

    private:

        MatrixControl control;
        glm::vec3 posicion;
        glm::vec3 scale;
        float yaw;
        float pitch;
        float roll;


    public:

        ModelMatrix();
        void setEulerAngles(float yaw, float pitch, float roll);
        void setPosition(const glm::vec3& position);
        void setScale(const glm::vec3& scale);
        glm::vec3 getPosition();
        glm::mat4 getTraslacion();
        glm::mat4 getOrientacion();
        glm::mat4 getModelMatrix();
        glm::mat3 getNormalMatrix();

};

inline ModelMatrix::ModelMatrix(): posicion(0,0,0), scale(1,1,1), yaw(0), pitch(0), roll(0){
    control.setTrue();
}

inline void ModelMatrix::setEulerAngles(float yaw, float pitch, float roll){
    this->yaw= yaw;
    this->pitch= pitch;
    this->roll= roll;
    control.cambioX= true;
    control.cambioY= true;
    control.cambioZ= true;
}

inline void ModelMatrix::setPosition(const glm::vec3& position){
    this->posicion= position;
    this->control.cambioTras= true;
}

inline void ModelMatrix::setScale(const glm::vec3& scale){
    this->scale= scale;
    this->control.cambioScale= true;
}

inline glm::vec3 ModelMatrix::getPosition(){
    return this->posicion;
}


}

#endif // HGSMODEL_H_INCLUDED
