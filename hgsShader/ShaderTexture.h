#ifndef SHADERTEXTURE_H_INCLUDED
#define SHADERTEXTURE_H_INCLUDED

#include "../hgsMaterial/material.h"
#include "ShaderProgram.h"
#include "../hgsVideo/ModelMatrix.h"
#include <glm/gtc/type_ptr.hpp>


namespace hgs{


struct LuzDireccion;
struct LuzPunto;
struct LuzLinterna;
struct Vao;

class ShaderTexture : public ShaderProgram{

    public:

        ShaderTexture();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setModelMatrix(ModelMatrix& modelMatrix) const;

        void setMaterial(const Material& material) const;

};


inline ShaderProgram * ShaderTexture::createCopy() const{
    return new ShaderTexture(*this);
}

inline ShaderProgram * ShaderTexture::createMove(){
    return new ShaderTexture(std::move(*this));
}

inline void ShaderTexture::setModelMatrix(ModelMatrix& modelMatrix) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(modelMatrix.getModelMatrix()));
    glUniformMatrix3fv(glGetUniformLocation(*this->idProgram,"normalMatrix"),1,GL_FALSE,value_ptr(modelMatrix.getNormalMatrix()));
}

inline void ShaderTexture::setMaterial(const Material& material) const{
    glActiveTexture(GL_TEXTURE0);
    material.map_Ka.usar();
    glActiveTexture(GL_TEXTURE1);
    material.map_Kd.usar();
    glActiveTexture(GL_TEXTURE2);
    material.map_Ks.usar();
    glUniform1f(glGetUniformLocation(*this->idProgram,"material.shininess"),material.Ns);
}

}

#endif // SHADERTEXTURE_H_INCLUDED
