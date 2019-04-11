#ifndef LUZPUNTO_H_INCLUDED
#define LUZPUNTO_H_INCLUDED

#include "atenuacion.h"

namespace hgs{

struct LuzPunto{

    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    Atenuacion aten;

    LuzPunto(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const Atenuacion& aten);

};

inline LuzPunto::LuzPunto(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const Atenuacion& aten)
: position(position), ambient(ambient), diffuse(diffuse), specular(specular), aten(aten){}


}

#endif // HGSLUZPUNTO_H_INCLUDED
