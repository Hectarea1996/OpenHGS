#ifndef SHADERSKYBOX_H_INCLUDED
#define SHADERSKYBOX_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/CubeMap.h"
#include <glm/gtc/type_ptr.hpp>

namespace hgs{

class ShaderSkybox : public ShaderProgram{

    public:

        ShaderSkybox();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setCubeMap(const CubeMap& cubeMap) const;

};

inline ShaderProgram * ShaderSkybox::createCopy() const{
    return new ShaderSkybox(*this);
}

inline ShaderProgram * ShaderSkybox::createMove(){
    return new ShaderSkybox(std::move(*this));
}

inline void ShaderSkybox::setCubeMap(const CubeMap& cubeMap) const{
    glActiveTexture(GL_TEXTURE0);
    cubeMap.usar();
}

}

#endif // SHADERSKYBOX_H_INCLUDED
