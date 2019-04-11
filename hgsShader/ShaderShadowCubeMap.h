#ifndef SHADERSHADOWCUBEMAP_H_INCLUDED
#define SHADERSHADOWCUBEMAP_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/ModelMatrix.h"
#include "../hgsVideo/ProjectionMatrix.h"
#include <glm/gtc/type_ptr.hpp>

namespace hgs{

class ShaderShadowCubeMap : public ShaderProgram{

    public:

        ShaderShadowCubeMap();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setModelMatrix(ModelMatrix& model) const;
        void setProjectionMatrix(ProjectionMatrix& projection) const;
        void setLightPosition(glm::vec3 lightPosition) const;

};

inline ShaderShadowCubeMap::ShaderShadowCubeMap()
: ShaderProgram("./Shaders/shadowCubeMapShader/shadowCubeMapShader.vs","./Shaders/shadowCubeMapShader/shadowCubeMapShader.gs","./Shaders/shadowCubeMapShader/shadowCubeMapShader.fs"){}

inline ShaderProgram * ShaderShadowCubeMap::createCopy() const{
    return new ShaderShadowCubeMap(*this);
}

inline ShaderProgram * ShaderShadowCubeMap::createMove(){
    return new ShaderShadowCubeMap(std::move(*this));
}

inline void ShaderShadowCubeMap::setModelMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
}

inline void ShaderShadowCubeMap::setProjectionMatrix(ProjectionMatrix& projection) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"projectionShadow"),1,GL_FALSE,value_ptr(projection.getProjectionMatrix()));
    glUniform1f(glGetUniformLocation(*this->idProgram,"far_plane"),projection.getFar());
}

}

#endif // SHADERSHADOWCUBEMAP_H_INCLUDED
