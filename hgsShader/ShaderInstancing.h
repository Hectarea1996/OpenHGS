#ifndef SHADERINSTANCING_H_INCLUDED
#define SHADERINSTANCING_H_INCLUDED


#include "ShaderProgram.h"
#include "../hgsVideo/ModelMatrix.h"
#include "../hgsVideo/OBJLoader.h"
#include "../hgsVideo/CubeMap.h"
#include <glm/gtc/type_ptr.hpp>



namespace hgs{

class ShaderInstancing : public virtual ShaderProgram{

    public:

        ShaderInstancing();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setCubeMap(const CubeMap& cubeMap) const;

        void setModelMatrix(ModelMatrix& model) const;
        void setModelPFMatrix(ModelMatrix& model) const;

        void setOffset(float offset) const;
        void setTotalModels(unsigned int totalModels) const;

        void setMaterial(const Material& material) const;

};

inline ShaderProgram * ShaderInstancing::createCopy() const{
    return new ShaderInstancing(*this);
}

inline ShaderProgram * ShaderInstancing::createMove(){
    return new ShaderInstancing(std::move(*this));
}

inline void ShaderInstancing::setCubeMap(const CubeMap& cubeMap) const{
    cubeMap.usar();
}

inline void ShaderInstancing::setModelMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
    glUniformMatrix3fv(glGetUniformLocation(*this->idProgram,"normalMatrix"),1,GL_FALSE,value_ptr(model.getNormalMatrix()));
}

inline void ShaderInstancing::setModelPFMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"modelPF"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
    glUniformMatrix3fv(glGetUniformLocation(*this->idProgram,"normalMatrixPF"),1,GL_FALSE,value_ptr(model.getNormalMatrix()));
}

inline void ShaderInstancing::setOffset(float offset) const{
    glUniform1f(glGetUniformLocation(*this->idProgram,"offset"),offset);
}

inline void ShaderInstancing::setTotalModels(unsigned int totalModels) const{
    glUniform1i(glGetUniformLocation(*this->idProgram,"totalModels"),totalModels);
}

inline void ShaderInstancing::setMaterial(const Material& material) const{
    glUniform3f(glGetUniformLocation(*this->idProgram,"material.ambient"),material.Ka.x,material.Ka.y,material.Ka.z);
    glUniform3f(glGetUniformLocation(*this->idProgram,"material.diffuse"),material.Kd.x,material.Kd.y,material.Kd.z);
    glUniform3f(glGetUniformLocation(*this->idProgram,"material.specular"),material.Ks.x,material.Ks.y,material.Ks.z);
    glUniform1f(glGetUniformLocation(*this->idProgram,"material.shininess"),material.Ns);
    glUniform1i(glGetUniformLocation(*this->idProgram,"material.illum"),material.illum);
}


}




#endif // SHADERINSTANCING_H_INCLUDED
