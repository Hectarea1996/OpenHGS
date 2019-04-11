#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "ModelMatrix.h"
#include "Mesh.h"
#include <vector>

namespace hgs{

struct Model{

    std::vector<Mesh> meshVector;
    ModelMatrix modelMatrix;

    template<class Mesh>
    Model(Mesh&& m);
    Model(const std::vector<Mesh>& meshVector);
    Model(std::vector<Mesh>&& meshVector);

    std::vector<Mesh>::iterator begin();
    std::vector<Mesh>::iterator end();

    void dibuja(unsigned int HGS_MODO_DIBUJO);

};

template<class Mesh>
inline Model::Model(Mesh&& m){
    this->meshVector.push_back(std::forward<Mesh>(m));
}

inline Model::Model(const std::vector<Mesh>& meshVector) : meshVector(meshVector){}

inline Model::Model(std::vector<Mesh>&& meshVector) : meshVector(meshVector){}

inline std::vector<Mesh>::iterator Model::begin(){
    return this->meshVector.begin();
}

inline std::vector<Mesh>::iterator Model::end(){
    return this->meshVector.end();
}

inline void Model::dibuja(unsigned int HGS_MODO_DIBUJO){
    for (const Mesh& mesh: this->meshVector){
        mesh.dibuja(HGS_MODO_DIBUJO);
    }
}


}

#endif // HGSMODEL_H_INCLUDED
