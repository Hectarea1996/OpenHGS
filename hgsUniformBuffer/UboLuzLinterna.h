#ifndef UBOLUZLINTERNA_H_INCLUDED
#define UBOLUZLINTERNA_H_INCLUDED


#include "../hgsVideo/LuzLinterna.h"


#define HGS_MAX_LUZ_LINTERNA   10

#define HGS_SIZE_STRUCT_LUZLIN      96

/*
layout (std140) uniform Name{
    int linEnc[MAX_DIRECCION];
    LuzLinterna luzLin[MAX_DIRECCION];
};
*/


namespace hgs{

template<unsigned int bindValue>
class UboLuzLinterna_impl: public UniformBuffer{

    private:

        UboLuzLinterna_impl();


    public:

        static const unsigned int max_luces= HGS_MAX_LUZ_LINTERNA;
        static UboLuzLinterna_impl<bindValue>& getInstancia();
        void setLuzLinterna(const LuzLinterna& luz, unsigned int indice);
        void quitarLuzLinterna(unsigned int indice);
        UboLuzLinterna_impl<bindValue>& operator=(const UboLuzLinterna_impl<bindValue>& otro)= delete;

};

template<unsigned int bindValue>
inline UboLuzLinterna_impl<bindValue>::UboLuzLinterna_impl()
: UniformBuffer(max_luces*HGS_SIZE_ARRAY_ELEMENT+max_luces*HGS_SIZE_STRUCT_LUZLIN,bindValue){}

template<unsigned int bindValue>
inline UboLuzLinterna_impl<bindValue>& UboLuzLinterna_impl<bindValue>::getInstancia(){
    static UboLuzLinterna_impl<bindValue> uboLuz;
    return uboLuz;
}

template<unsigned int bindValue>
void UboLuzLinterna_impl<bindValue>::setLuzLinterna(const LuzLinterna& luz, unsigned int indice){
    int encendido= 1;
    int luzlinOffset= HGS_SIZE_ARRAY_ELEMENT*this->max_luces+HGS_SIZE_STRUCT_LUZLIN*indice;
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,HGS_SIZE_ARRAY_ELEMENT*indice,HGS_SIZE_ARRAY_ELEMENT,&encendido);
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset                                                           ,HGS_SIZE_VEC3,glm::value_ptr(luz.position));
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3                                       ,HGS_SIZE_VEC3,glm::value_ptr(luz.direccion));
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*2                                     ,HGS_SIZE_VEC3,glm::value_ptr(luz.ambient));
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*3                                     ,HGS_SIZE_VEC3,glm::value_ptr(luz.diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*4                                     ,HGS_SIZE_VEC3,glm::value_ptr(luz.specular));
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*4+HGS_SIZE_VEC3                       ,HGS_SIZE_FLOAT,&luz.aten.constant);
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*4+HGS_SIZE_VEC3+HGS_ALLIGNMENT_FLOAT  ,HGS_SIZE_FLOAT,&luz.aten.linear);
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*4+HGS_SIZE_VEC3+HGS_ALLIGNMENT_FLOAT*2,HGS_SIZE_FLOAT,&luz.aten.quadratic);
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*4+HGS_SIZE_VEC3+HGS_ALLIGNMENT_FLOAT*3,HGS_SIZE_FLOAT,&luz.phiIn);
    glBufferSubData(GL_UNIFORM_BUFFER,luzlinOffset+HGS_ALLIGNMENT_VEC3*4+HGS_SIZE_VEC3+HGS_ALLIGNMENT_FLOAT*4,HGS_SIZE_FLOAT,&luz.phiOut);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

template<unsigned int bindValue>
inline void UboLuzLinterna_impl<bindValue>::quitarLuzLinterna(unsigned int indice){
    int encendido= 0;
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,HGS_SIZE_ARRAY_ELEMENT*indice,HGS_SIZE_ARRAY_ELEMENT,&encendido);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}


using UboLuzLinterna= UboLuzLinterna_impl<4>;

}

#endif // UBOLUZLINTERNA_H_INCLUDED
