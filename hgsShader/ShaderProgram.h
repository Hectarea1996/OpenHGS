#ifndef SHADERPROGRAM_H_INCLUDED
#define SHADERPROGRAM_H_INCLUDED


#include "glad/glad.h"
#include "../hgsVideo/OBJLoader.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>



namespace hgs{

class Mesh;
class Model;
class Vao;

class ShaderProgram{

    protected:

        std::shared_ptr<unsigned> idProgram;


    public:

        ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
        ShaderProgram(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath);
        virtual ~ShaderProgram(){}
        virtual ShaderProgram * createCopy() const = 0;
        virtual ShaderProgram * createMove() = 0;

        virtual Vao createVao(const VaoInfo& vaoInfo) const = 0;
        Mesh createMesh(const MeshInfo& m) const;
        Model createModel(const std::vector<hgs::MeshInfo>& vm) const;

        void usar() const;

};



inline void ShaderProgram::usar() const{
    glUseProgram(*this->idProgram);
}


}

#endif // SHADERPROGRAM_H_INCLUDED
