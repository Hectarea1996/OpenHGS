
#include "CubeMap.h"
#include "../hgsVideo/stb_image.h"
#include "../hgsVideo/Texture.h"
#include <iostream>
using namespace hgs;
using namespace std;

static void deleteCubeMap(unsigned int * cubeMapId){

    glDeleteTextures(1,cubeMapId);
    delete cubeMapId;

}

static std::array<std::string,6> getExample(unsigned int HGS_EXAMPLE){

    array<string,6> cubemapString;

    switch (HGS_EXAMPLE){
        case HGS_EXAMPLE_DOWNUNDER:
            cubemapString[HGS_CUBE_MAP_BACK]= "./Cubemaps/mp_downunder/down-under_bk.tga";
            cubemapString[HGS_CUBE_MAP_BOTTOM]= "./Cubemaps/mp_downunder/down-under_dn.tga";
            cubemapString[HGS_CUBE_MAP_FRONT]= "./Cubemaps/mp_downunder/down-under_ft.tga";
            cubemapString[HGS_CUBE_MAP_LEFT]= "./Cubemaps/mp_downunder/down-under_lf.tga";
            cubemapString[HGS_CUBE_MAP_RIGHT]= "./Cubemaps/mp_downunder/down-under_rt.tga";
            cubemapString[HGS_CUBE_MAP_TOP]= "./Cubemaps/mp_downunder/down-under_up.tga";
            break;
        case HGS_EXAMPLE_DESERT:
            cubemapString[HGS_CUBE_MAP_BACK]= "./Cubemaps/ame_fade/fadeaway_bk.tga";
            cubemapString[HGS_CUBE_MAP_BOTTOM]= "./Cubemaps/ame_fade/fadeaway_dn.tga";
            cubemapString[HGS_CUBE_MAP_FRONT]= "./Cubemaps/ame_fade/fadeaway_ft.tga";
            cubemapString[HGS_CUBE_MAP_LEFT]= "./Cubemaps/ame_fade/fadeaway_lf.tga";
            cubemapString[HGS_CUBE_MAP_RIGHT]= "./Cubemaps/ame_fade/fadeaway_rt.tga";
            cubemapString[HGS_CUBE_MAP_TOP]= "./Cubemaps/ame_fade/fadeaway_up.tga";
            break;
        case HGS_EXAMPLE_PLANTS:
            cubemapString[HGS_CUBE_MAP_BACK]= "./Cubemaps/mp_organic/organic_bk.tga";
            cubemapString[HGS_CUBE_MAP_BOTTOM]= "./Cubemaps/mp_organic/organic_dn.tga";
            cubemapString[HGS_CUBE_MAP_FRONT]= "./Cubemaps/mp_organic/organic_ft.tga";
            cubemapString[HGS_CUBE_MAP_LEFT]= "./Cubemaps/mp_organic/organic_lf.tga";
            cubemapString[HGS_CUBE_MAP_RIGHT]= "./Cubemaps/mp_organic/organic_rt.tga";
            cubemapString[HGS_CUBE_MAP_TOP]= "./Cubemaps/mp_organic/organic_up.tga";
            break;
    }

    return cubemapString;

}

CubeMap::CubeMap(const std::array<std::string,6>& textures, const TextureData& textureData)
: cubeMapId(new unsigned int(0),deleteCubeMap){

    glGenTextures(1,this->cubeMapId.get());
    glBindTexture(GL_TEXTURE_CUBE_MAP,*this->cubeMapId);

    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,textureData.hgsWrapHor);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,textureData.hgsWrapVer);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,textureData.hgsWrapProf);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,textureData.hgsMinFilter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,textureData.hgsMagFilter);

    int ancho, alto, numCanales;
    unsigned char * imagen;

    for (int i=0; i<6; i++){
        imagen= stbi_load(textures[i].c_str(),&ancho,&alto,&numCanales,0);
        if (imagen==nullptr){
            cout << "Error al leer la imagen: " << textures[i] << endl;
            exit(EXIT_FAILURE);
        }

        if (numCanales==3)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,imagen);
        else if (numCanales==4)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGBA,ancho,alto,0,GL_RGBA,GL_UNSIGNED_BYTE,imagen);

        stbi_image_free(imagen);
    }

    if (textureData.hgsMinFilter>=HGS_MIPMAP_NEAR_NEAR && textureData.hgsMinFilter<=HGS_MIPMAP_LIN_LIN){
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }

}

CubeMap::CubeMap(unsigned int HGS_EXAMPLE): CubeMap(getExample(HGS_EXAMPLE)){


}
