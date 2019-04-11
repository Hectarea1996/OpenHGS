#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "../hgsVideo/Texture.h"
#include <glm/vec3.hpp>

namespace hgs{

struct Material{

    // Material Name
    std::string name;
    // Ambient Color
    glm::vec3 Ka;
    // Diffuse Color
    glm::vec3 Kd;
    // Specular Color
    glm::vec3 Ks;
    // Specular Exponent
    float Ns;
    // Optical Density
    float Ni;
    // Dissolve
    float d;
    // Illumination
    int illum;
    // Ambient Texture Map
    Texture map_Ka;
    // Diffuse Texture Map
    Texture map_Kd;
    // Specular Texture Map
    Texture map_Ks;
    // Specular Hightlight Map
    Texture map_Ns;
    // Alpha Texture Map
    Texture map_d;
    // Bump Map
    Texture map_bump;

    Material();
    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);
    template <class Texture>
    Material(float shininess, Texture&& ambientTex, Texture&& diffuseTex, Texture&& specularTex);
//    template<class Texture>
//    material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
//                Texture&& ambientTex, Texture&& diffuseTex, Texture&& specularTex, float shininess);

};

inline Material::Material(): Ka(1,1,1), Kd(1,1,1), Ks(1,1,1), Ns(32){}

inline Material::Material(const glm::vec3& Ka, const glm::vec3& Kd, const glm::vec3& Ks, float Ns)
: Ka(Ka), Kd(Kd), Ks(Ks), Ns(Ns){}

template<class Texture>
inline Material::Material(float shininess, Texture&& ambientTex, Texture&& diffuseTex, Texture&& specularTex)
: Ns(shininess), map_Ka(std::forward<Texture>(ambientTex)), map_Kd(std::forward<Texture>(diffuseTex)), map_Ks(std::forward<Texture>(specularTex)){}

//template<class Texture>
//inline material::material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
//                                Texture&& ambientTex, Texture&& diffuseTex, Texture&& specularTex, float shininess)
//: ambient(ambient), diffuse(diffuse), specular(specular),
//  ambientTex(std::forward<Texture>(ambientTex)), diffuseTex(std::forward<Texture>(diffuseTex)), specularTex(std::forward<Texture>(specularTex)), shininess(shininess){}


}

#endif // MATERIAL_H_INCLUDED
