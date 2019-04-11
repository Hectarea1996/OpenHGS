#ifndef SHADERSHADOW_H_INCLUDED
#define SHADERSHADOW_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/ProjectionMatrix.h"
#include "../hgsVideo/ViewMatrix.h"
#include "../hgsVideo/ModelMatrix.h"
#include <glm/gtc/type_ptr.hpp>

namespace hgs{

class ShaderShadow : public ShaderProgram{

    public:

        ShaderShadow();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setModelMatrix(ModelMatrix& model) const;
        void setProjectionMatrix(ProjectionMatrix& projection) const;
        void setViewMatrix(ViewMatrix& view) const;

};

inline ShaderShadow::ShaderShadow()
: ShaderProgram("./Shaders/shadowShader/shadowShader.vs","./Shaders/shadowShader/shadowShader.fs"){}

inline ShaderProgram * ShaderShadow::createCopy() const{
    return new ShaderShadow(*this);
}

inline ShaderProgram * ShaderShadow::createMove(){
    return new ShaderShadow(std::move(*this));
}

inline void ShaderShadow::setModelMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
}


inline void ShaderShadow::setProjectionMatrix(ProjectionMatrix& projection) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"projection"),1,GL_FALSE,value_ptr(projection.getProjectionMatrix()));
}

inline void ShaderShadow::setViewMatrix(ViewMatrix& view) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"view"),1,GL_FALSE,value_ptr(view.getViewMatrix()));
    //glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"view"),1,GL_FALSE,value_ptr(glm::lookAt(glm::vec3(0,-3,0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0))));
}


}


#endif // SHADERSHADOW_H_INCLUDED
