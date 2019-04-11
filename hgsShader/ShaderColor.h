#ifndef SHADERCOLOR_H_INCLUDED
#define SHADERCOLOR_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/ModelMatrix.h"
#include "../hgsVideo/OBJLoader.h"
#include "../hgsVideo/CubeMap.h"
#include <glm/gtc/type_ptr.hpp>



namespace hgs{

class ShaderColor : public virtual ShaderProgram{

    public:

        ShaderColor();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setSkybox(const CubeMap& cubeMap) const;

        void setModelMatrix(ModelMatrix& model) const;
        void setMaterial(const Material& material) const;

        void setLightDirSpaceMatrix(const glm::mat4 lightMatrix) const;
        void setLightPoint_farPlane(float farPlane) const;

        void setShadowDirMap(const Texture& shadowMap) const;
        void setShadowPunMap(const CubeMap& shadowPunMap) const;

};

inline ShaderProgram * ShaderColor::createCopy() const{
    return new ShaderColor(*this);
}

inline ShaderProgram * ShaderColor::createMove(){
    return new ShaderColor(std::move(*this));
}

inline void ShaderColor::setSkybox(const CubeMap& cubeMap) const{
    glActiveTexture(GL_TEXTURE0);
    cubeMap.usar();
}

inline void ShaderColor::setModelMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
    glUniformMatrix3fv(glGetUniformLocation(*this->idProgram,"normalMatrix"),1,GL_FALSE,value_ptr(model.getNormalMatrix()));

}

inline void ShaderColor::setLightDirSpaceMatrix(const glm::mat4 lightMatrix) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"lightSpaceMatrix"),1,GL_FALSE,value_ptr(lightMatrix));
}

inline void ShaderColor::setShadowDirMap(const Texture& shadowDirMap) const{
    glActiveTexture(GL_TEXTURE1);
    shadowDirMap.usar();
}

inline void ShaderColor::setShadowPunMap(const CubeMap& shadowPunMap) const{
    glActiveTexture(GL_TEXTURE2);
    shadowPunMap.usar();
}

inline void ShaderColor::setLightPoint_farPlane(float farPlane) const{
    glUniform1f(glGetUniformLocation(*this->idProgram,"far_plane"),farPlane);
}

inline void ShaderColor::setMaterial(const Material& material) const{
    glUniform3f(glGetUniformLocation(*this->idProgram,"material.ambient"),material.Ka.x,material.Ka.y,material.Ka.z);
    glUniform3f(glGetUniformLocation(*this->idProgram,"material.diffuse"),material.Kd.x,material.Kd.y,material.Kd.z);
    glUniform3f(glGetUniformLocation(*this->idProgram,"material.specular"),material.Ks.x,material.Ks.y,material.Ks.z);
    glUniform1f(glGetUniformLocation(*this->idProgram,"material.shininess"),material.Ns);
    glUniform1i(glGetUniformLocation(*this->idProgram,"material.illum"),material.illum);
}


}


#endif // SHADERCOLOR_H_INCLUDED
