#ifndef LUZLINTERNA_H_INCLUDED
#define LUZLINTERNA_H_INCLUDED

#include "atenuacion.h"

namespace hgs{

struct LuzLinterna{

    glm::vec3 position;
    glm::vec3 direccion;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Atenuacion aten;
    float phiIn;
    float phiOut;

    LuzLinterna(const glm::vec3& position, const glm::vec3& direccion, const glm::vec3& ambient, const glm::vec3& diffuse,
                   const glm::vec3& specular, float phiIn, float phiOut, const Atenuacion& aten);

};

inline LuzLinterna::LuzLinterna(const glm::vec3& position, const glm::vec3& direccion, const glm::vec3& ambient,
                                      const glm::vec3& diffuse, const glm::vec3& specular, float phiIn, float phiOut,
                                      const Atenuacion& aten)
: position(position), direccion(direccion), ambient(ambient), diffuse(diffuse), specular(specular), aten(aten), phiIn(glm::cos(phiIn)),
  phiOut(glm::cos(phiOut)){}


}

#endif // LUZLINTERNA_H_INCLUDED
