#ifndef SHADERCUBEMAP_H_INCLUDED
#define SHADERCUBEMAP_H_INCLUDED

#include "ShaderProgram.h"
#include "../hgsVideo/CubeMap.h"
#include <glm/gtc/type_ptr.hpp>

namespace hgs{

class ShaderCubeMap : public ShaderProgram{

    public:

        ShaderCubeMap();
        ShaderProgram * createCopy() const;
        ShaderProgram * createMove();

        Vao createVao(const VaoInfo& vaoInfo) const;

        void setCubeMap(const CubeMap& cubeMap) const;

};

inline ShaderProgram * ShaderCubeMap::createCopy() const{
    return new ShaderCubeMap(*this);
}

inline ShaderProgram * ShaderCubeMap::createMove(){
    return new ShaderCubeMap(std::move(*this));
}

inline void ShaderCubeMap::setCubeMap(const CubeMap& cubeMap) const{
    glActiveTexture(GL_TEXTURE0);
    cubeMap.usar();
}

}

#endif // SHADERCUBEMAP_H_INCLUDED
