#ifndef SHADERDEPTH_H_INCLUDED
#define SHADERDEPTH_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/ModelMatrix.h"
#include <glm/gtc/type_ptr.hpp>

namespace hgs{

class ShaderDepth : public ShaderProgram{

    public:

        ShaderDepth();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setModelMatrix(ModelMatrix& model) const;
        void setDepthMap(const Texture& textura) const;

};

inline ShaderDepth::ShaderDepth()
: ShaderProgram("./Shaders/depthShader/depthShader.vs","./Shaders/depthShader/depthShader.fs"){
    glUseProgram(*this->idProgram);
    glUniform1i(glGetUniformLocation(*this->idProgram,"depthMap"),0);
}

inline ShaderProgram * ShaderDepth::createCopy() const{
    return new ShaderDepth(*this);
}

inline ShaderProgram * ShaderDepth::createMove(){
    return new ShaderDepth(std::move(*this));
}

inline void ShaderDepth::setModelMatrix(ModelMatrix& model) const{
    glUniformMatrix4fv(glGetUniformLocation(*this->idProgram,"model"),1,GL_FALSE,value_ptr(model.getModelMatrix()));
}

inline void ShaderDepth::setDepthMap(const Texture& textura) const{
    glActiveTexture(GL_TEXTURE0);
    textura.usar();
}

}


#endif // SHADERDEPTH_H_INCLUDED
