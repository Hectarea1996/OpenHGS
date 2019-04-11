#ifndef SHADERMAP_H_INCLUDED
#define SHADERMAP_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/ModelMatrix.h"
#include <glm/gtc/type_ptr.hpp>

namespace hgs{

class ShaderMap: public ShaderProgram{

    public:

        ShaderMap();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setModelMatrix(ModelMatrix& model) const;
        void setMap(const Texture& texture) const;

};

inline ShaderMap::ShaderMap()
: ShaderProgram("./Shaders/mapShader/mapShader.vs","./Shaders/mapShader/mapShader.fs"){
    glUseProgram(*this->idProgram);
    glUniform1i(glGetUniformLocation(*this->idProgram,"map"),0);
}

inline ShaderProgram * ShaderMap::createCopy() const{
    return new ShaderMap(*this);
}

inline ShaderProgram * ShaderMap::createMove(){
    return new ShaderMap(std::move(*this));
}

inline void ShaderMap::setModelMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
}

inline void ShaderMap::setMap(const Texture& texture) const{
    glActiveTexture(GL_TEXTURE0);
    texture.usar();
}

}


#endif // SHADERMAP_H_INCLUDED
