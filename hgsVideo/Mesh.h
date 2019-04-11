#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Vao.h"
#include "../hgsMaterial/material.h"
#include <string>


namespace hgs{


struct Mesh{

    private:

        static Texture createTexture(const std::string& nombre){
            if (nombre.empty())
                return Texture();
            return Texture(nombre);
        }


    public:

        std::string nombre;
        Vao vao;
        Material meshMaterial;


        template<class VAO>
        Mesh(VAO&& vao, const Material& mat);
        template<class String, class VAO>
        Mesh(String&& nombre, VAO&& vao, const Material& mat);
        ~Mesh(){}

        const std::string& getNombre() const;

        //Buscar wireframe mode.
        void dibuja(int HGS_MODO_DIBUJO) const;
        void dibuja(int HGS_MODO_DIBUJO, unsigned int cantidad) const;

};

template<class VAO>
Mesh::Mesh(VAO&& vao, const Material& mat)
: vao(std::forward<VAO>(vao)), meshMaterial(mat){}

template<class String, class VAO>
inline Mesh::Mesh(String&& nombre, VAO&& vao, const Material& mat)
: nombre(std::forward<String>(nombre)), vao(std::forward<VAO>(vao)), meshMaterial(mat){}

inline const std::string& Mesh::getNombre() const{
    return this->nombre;
}

inline void Mesh::dibuja(int HGS_MODO_DIBUJO) const{
    this->vao.dibuja(HGS_MODO_DIBUJO);
}

inline void Mesh::dibuja(int HGS_MODO_DIBUJO, unsigned int cantidad) const{
    this->vao.dibuja(HGS_MODO_DIBUJO,cantidad);
}

}

#endif // MESH_H_INCLUDED
