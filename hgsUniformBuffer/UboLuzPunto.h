#ifndef UBOLUZPUNTO_H_INCLUDED
#define UBOLUZPUNTO_H_INCLUDED


#include "../hgsVideo/LuzPunto.h"

#define HGS_MAX_LUZ_PUNTO   10
#define HGS_SIZE_STRUCT_LUZPUNTO    80

/*
struct LuzPunto{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

layout (std140) uniform Name{
    int punEnc[MAX_DIRECCION];
    LuzPunto luzPun[MAX_DIRECCION];
};
*/


namespace hgs{

template<unsigned int bindValue>
class UboLuzPunto_impl: public UniformBuffer{

    private:

        UboLuzPunto_impl();


    public:

        static const unsigned int max_luces= HGS_MAX_LUZ_PUNTO;
        static UboLuzPunto_impl<bindValue>& getInstancia();
        void setLuzPunto(const LuzPunto& luz, unsigned int indice);
        void quitarLuzPunto(unsigned int indice);
        UboLuzPunto_impl<bindValue>& operator=(const UboLuzPunto_impl<bindValue>& otro)= delete;

};

template<unsigned int bindValue>
inline UboLuzPunto_impl<bindValue>::UboLuzPunto_impl()
: UniformBuffer(max_luces*HGS_SIZE_ARRAY_ELEMENT+max_luces*HGS_SIZE_STRUCT_LUZPUNTO,bindValue){}

template<unsigned int bindValue>
inline UboLuzPunto_impl<bindValue>& UboLuzPunto_impl<bindValue>::getInstancia(){
    static UboLuzPunto_impl<bindValue> uboLuz;
    return uboLuz;
}

template<unsigned int bindValue>
void UboLuzPunto_impl<bindValue>::setLuzPunto(const LuzPunto& luz, unsigned int indice){
    int encendido= 1;
    int luzdirOffset= HGS_SIZE_ARRAY_ELEMENT*this->max_luces+HGS_SIZE_STRUCT_LUZPUNTO*indice;
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,HGS_SIZE_ARRAY_ELEMENT*indice,HGS_SIZE_ARRAY_ELEMENT,&encendido);
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset,HGS_SIZE_VEC3,glm::value_ptr(luz.position));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_ALLIGNMENT_VEC3,HGS_SIZE_VEC3,glm::value_ptr(luz.ambient));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_ALLIGNMENT_VEC3*2,HGS_SIZE_VEC3,glm::value_ptr(luz.diffuse));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_ALLIGNMENT_VEC3*3,HGS_SIZE_VEC3,glm::value_ptr(luz.specular));
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_ALLIGNMENT_VEC3*3+HGS_SIZE_VEC3,HGS_SIZE_FLOAT,&luz.aten.constant);
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_ALLIGNMENT_VEC3*3+HGS_SIZE_VEC3+HGS_SIZE_FLOAT,HGS_SIZE_FLOAT,&luz.aten.linear);
    glBufferSubData(GL_UNIFORM_BUFFER,luzdirOffset+HGS_ALLIGNMENT_VEC3*3+HGS_SIZE_VEC3+HGS_SIZE_FLOAT*2,HGS_SIZE_FLOAT,&luz.aten.quadratic);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

template<unsigned int bindValue>
inline void UboLuzPunto_impl<bindValue>::quitarLuzPunto(unsigned int indice){
    int encendido= 0;
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,HGS_SIZE_ARRAY_ELEMENT*indice,HGS_SIZE_ARRAY_ELEMENT,&encendido);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}


using UboLuzPunto= UboLuzPunto_impl<3>;

}

#endif // UBOLUZPUNTO_H_INCLUDED
