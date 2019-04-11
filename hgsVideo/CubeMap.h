#ifndef CUBEMAP_H_INCLUDED
#define CUBEMAP_H_INCLUDED


#include "../hgsVideo/Texture.h"
#include <memory>


#define HGS_CUBE_MAP_RIGHT      0
#define HGS_CUBE_MAP_LEFT       1
#define HGS_CUBE_MAP_TOP        2
#define HGS_CUBE_MAP_BOTTOM     3
#define HGS_CUBE_MAP_BACK       4
#define HGS_CUBE_MAP_FRONT      5

#define HGS_EXAMPLE_DESERT      0
#define HGS_EXAMPLE_DOWNUNDER   1
#define HGS_EXAMPLE_PLANTS      2


namespace hgs{

class Texture;

class CubeMap{

    private:

        std::shared_ptr<unsigned int> cubeMapId;


    public:

        CubeMap();
        CubeMap(unsigned int HGS_EXAMPLE);
        CubeMap(const std::array<std::string,6>& textures);
        CubeMap(const std::array<std::string,6>& textures, const TextureData& textureData);
        void usar() const;

        unsigned int getCubeMapId();


};

inline CubeMap::CubeMap(): cubeMapId(new unsigned(0)){
    glGenTextures(1,this->cubeMapId.get());
}

inline CubeMap::CubeMap(const std::array<std::string,6>& textures)
: CubeMap(textures,TextureData(HGS_WRAP_CLAMP_EDGE,HGS_WRAP_CLAMP_EDGE,HGS_FILTER_LINEAR,HGS_FILTER_LINEAR,false)){}

inline void CubeMap::usar() const{
    glBindTexture(GL_TEXTURE_CUBE_MAP,*this->cubeMapId);
}

inline unsigned int CubeMap::getCubeMapId(){
    return *this->cubeMapId;
}

}


#endif // CUBEMAP_H_INCLUDED
