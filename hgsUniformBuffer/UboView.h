#ifndef UBOVIEW_H_INCLUDED
#define UBOVIEW_H_INCLUDED

#include "../hgsVideo/ViewMatrix.h"
#include "UniformBuffer.h"

/*
layout (std140) uniform Name{
    mat4 view;
    vec3 viewPosition;
};
*/


namespace hgs{

template<unsigned int bindValue>
class UboView_impl: public UniformBuffer{

    private:

        UboView_impl();


    public:

        static UboView_impl<bindValue>& getInstancia();
        void setViewMatrix(const glm::mat4& view);
        UboView_impl<bindValue>& operator=(const UboView_impl<bindValue>& otro)= delete;

};

template<unsigned int bindValue>
inline UboView_impl<bindValue>::UboView_impl(): UniformBuffer(HGS_SIZE_MAT4,bindValue){}

template<unsigned int bindValue>
inline UboView_impl<bindValue>& UboView_impl<bindValue>::getInstancia(){
    static UboView_impl<bindValue> uboMatrices;
    return uboMatrices;
}

template<unsigned int bindValue>
inline void UboView_impl<bindValue>::setViewMatrix(const glm::mat4& view){
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,0,HGS_SIZE_MAT4,glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}


using UboView= UboView_impl<1>;

}


#endif // UBOVIEW_H_INCLUDED
