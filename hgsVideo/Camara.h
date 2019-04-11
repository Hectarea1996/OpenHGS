#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ViewMatrix.h"
#include "ProjectionMatrix.h"

namespace hgs{

class Camara{

    public:

        ViewMatrix view;
        ProjectionMatrix projection;

        Camara(float ancho, float alto);

        glm::vec3 getPosicion();
        glm::vec3 getDelante();
        glm::vec3 getDerecha();
        glm::vec3 getArriba();
        void setPosicion(const glm::vec3& posicion);
        void setEulerAngles(float yaw, float pitch, float roll);
        void lookAt(const glm::vec3& center);
        void lookAt(const glm::vec3& eye, const glm::vec3& center);

};

inline Camara::Camara(float ancho, float alto)
: projection(){
    this->projection.setPerspective(ancho,alto,glm::radians(45.0f),0.1f,100.0f);
}

inline void Camara::setEulerAngles(float yaw, float pitch, float roll){
    this->view.setEulerAngles(yaw,pitch,roll);
}

inline void Camara::setPosicion(const glm::vec3& posicion){
    this->view.setPosition(posicion);
}

inline glm::vec3 Camara::getPosicion(){
    return this->view.getPosition();
}

inline glm::vec3 Camara::getDelante(){
    return (glm::vec3)(transpose(this->view.getOrientacion())*glm::vec4(0,0,-1,1));
}

inline glm::vec3 Camara::getDerecha(){
    return (glm::vec3)(transpose(this->view.getOrientacion())*glm::vec4(1,0,0,1));
}

inline glm::vec3 Camara::getArriba(){
    return (glm::vec3)(transpose(this->view.getOrientacion())*glm::vec4(0,1,0,1));
}

inline void Camara::lookAt(const glm::vec3& center){
    this->view.lookAt(center);
}

inline void Camara::lookAt(const glm::vec3& eye, const glm::vec3& center){
    this->view.lookAt(eye,center);
}


}


#endif // CAMARA_H_INCLUDED
