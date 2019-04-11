#ifndef UBOLUZDIRECCION_H_INCLUDED
#define UBOLUZDIRECCION_H_INCLUDED

#define HGS_MAX_LUZ_DIRECCION   5

#include "UniformBuffer.h"
#include "../hgsVideo/LuzDireccion.h"

/*
struct LuzDireccion{
    vec3 direccion;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (std140) uniform Name{
    int dirEnc[MAX_DIRECCION];
    LuzDireccion luzDir[MAX_DIRECCION];
};
*/


namespace hgs{

template<unsigned int bindValue>
class UboLuzDireccion_impl: public UniformBuffer{

    private:

        UboLuzDireccion_impl();


    public:

        static const unsigned int max_luces= HGS_MAX_LUZ_DIRECCION;
        static UboLuzDireccion_impl<bindValue>& getInstancia();
        void setLuzDireccion(const LuzDireccion& luz, unsigned int indice);
        void quitarLuzDireccion(unsigned int indice);
        UboLuzDireccion_impl<bindValue>& operator=(const UboLuzDireccion_impl<bindValue>& otro)= delete;

};

template<unsigned int bindValue>
inline UboLuzDireccion_impl<bindValue>::UboLuzDireccion_impl()
: UniformBuffer(max_luces*HGS_SIZE_ARRAY_ELEMENT+max_luces*HGS_SIZE_VEC4*4,bindValue){}

template<unsigned int bindValue>
inline UboLuzDireccion_impl<bindValue>& UboLuzDireccion_impl<bindValue>::getInstancia(){
    static UboLuzDireccion_impl<bindValue> uboLuz;
    return uboLuz;
}

template<unsigned int bindValue>
void UboLuzDireccion_impl<bindValue>::setLuzDireccion(const LuzDireccion& luz, unsigned int indice){
    int encendido= 1;
    int luzdirOffset= HGS_SIZE_ARRAY_ELEMENT*this->max_luces+HGS_SIZE_VEC3*4*indice;
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,HGS_SIZE_ARRAY_ELEMENT*indice,HGS_SIZE_ARRAY_ELEMENT,&encendido);
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset,HGS_SIZE_VEC3,glm::value_ptr(luz.direccion));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_SIZE_VEC3,HGS_SIZE_VEC3,glm::value_ptr(luz.ambient));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_SIZE_VEC3*2,HGS_SIZE_VEC3,glm::value_ptr(luz.diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_SIZE_VEC3*3,HGS_SIZE_VEC3,glm::value_ptr(luz.specular));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

template<unsigned int bindValue>
inline void UboLuzDireccion_impl<bindValue>::quitarLuzDireccion(unsigned int indice){
    int encendido= 0;
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,HGS_SIZE_ARRAY_ELEMENT*indice,HGS_SIZE_ARRAY_ELEMENT,&encendido);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}


using UboLuzDireccion= UboLuzDireccion_impl<2>;

}


#endif // UBOLUZDIRECCION_H_INCLUDED
