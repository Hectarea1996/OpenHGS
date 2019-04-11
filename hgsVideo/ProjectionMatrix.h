#ifndef PROJECTIONMATRIX_H_INCLUDED
#define PROJECTIONMATRIX_H_INCLUDED

#include <glm/glm.hpp>


namespace hgs{

class ProjectionMatrix{

    private:

        bool inicializado;
        unsigned int modo;
        float left;
        float right;
        float bottom;
        float top;
        float _near;
        float _far;
        float fov;


    public:

        ProjectionMatrix();
        glm::mat4 getProjectionMatrix();
        void setPerspective(float ancho, float alto, float fov, float near, float far);
        void setOrthogonal(float left, float right, float bottom, float top, float near, float far);

        float getNear();
        float getFar();
        float getFov();

};

inline ProjectionMatrix::ProjectionMatrix(): inicializado(false){}

inline float ProjectionMatrix::getNear(){
    return this->_near;
}

inline float ProjectionMatrix::getFar(){
    return this->_far;
}

inline float ProjectionMatrix::getFov(){
    return this->fov;
}

}


#endif // PROJECTIONMATRIX_H_INCLUDED
