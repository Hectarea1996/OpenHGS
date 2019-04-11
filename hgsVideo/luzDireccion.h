#ifndef LUZDIRECCION_H_INCLUDED
#define LUZDIRECCION_H_INCLUDED


namespace hgs{

struct LuzDireccion{

    glm::vec3 direccion;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    LuzDireccion(const glm::vec3& direccion, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

};

inline LuzDireccion::LuzDireccion(const glm::vec3& direccion, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
: direccion(direccion), ambient(ambient), diffuse(diffuse), specular(specular){}

}

#endif // LUZDIRECCION_H_INCLUDED
