#ifndef UBOPROJECTION_H_INCLUDED
#define UBOPROJECTION_H_INCLUDED

#include "UniformBuffer.h"
#include "../hgsVideo/ProjectionMatrix.h"


/*
layout (std140) uniform Name{
    mat4 projection;
};
*/


namespace hgs{

template<unsigned int bindValue>
class UboProjection_impl: public UniformBuffer{

    private:

        UboProjection_impl();


    public:

        static UboProjection_impl<bindValue>& getInstancia();
        void setProjectionMatrix(const glm::mat4& projection);
        UboProjection_impl<bindValue>& operator=(const UboProjection_impl<bindValue>& otro)= delete;

};

template<unsigned int bindValue>
inline UboProjection_impl<bindValue>::UboProjection_impl(): UniformBuffer(HGS_SIZE_MAT4,bindValue){}

template<unsigned int bindValue>
inline UboProjection_impl<bindValue>& UboProjection_impl<bindValue>::getInstancia(){
    static UboProjection_impl<bindValue> uboMatrices;
    return uboMatrices;
}

template<unsigned int bindValue>
inline void UboProjection_impl<bindValue>::setProjectionMatrix(const glm::mat4& projection){
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,0,HGS_SIZE_MAT4,glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}


using UboProjection= UboProjection_impl<0>;

}


#endif // UBOPROJECTION_H_INCLUDED
