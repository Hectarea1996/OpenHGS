
#include "ShaderProgram.h"
#include "../hgsVideo/Model.h"
#include "../hgsVideo/Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
using namespace hgs;

static void deleteShaderProgram(unsigned int * idProgram){
    glDeleteProgram(*idProgram);
}

ShaderProgram::ShaderProgram(const string& vertexPath, const string& fragmentPath)
: idProgram(new unsigned(0),deleteShaderProgram){

    //Abrimos los ficheros y los convertimos en char*.
    string vertexCode;
    string fragmentCode;
    ifstream fileVertex;
    ifstream fileFragment;
    fileVertex.exceptions(ifstream::failbit | ifstream::badbit);
    fileFragment.exceptions(ifstream::failbit | ifstream::badbit);
    try{
        fileVertex.open(vertexPath);
        fileFragment.open(fragmentPath);

        stringstream vStream,fStream;
        vStream << fileVertex.rdbuf();
        fStream << fileFragment.rdbuf();

        vertexCode= vStream.str();
        fragmentCode= fStream.str();
    }catch(ifstream::failure e){
        cout << "hgsShader Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    const char* vCode= vertexCode.c_str();
    const char* fCode= fragmentCode.c_str();

    //Compilamos vertex shader
    unsigned int Vertex;
    int success;
    char infoLog[512];

    Vertex= glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Vertex,1,&vCode,nullptr);
    glCompileShader(Vertex);
    glGetShaderiv(Vertex,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(Vertex,512,nullptr,infoLog);
        cout << "hgsShader Error al compilar vertex shader: " << vertexPath << "\n" << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //Compilamos fragment shader
    unsigned int fragment;

    fragment= glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fCode,nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(fragment,512,nullptr,infoLog);
        cout << "hgsShader Error al compilar fragment shader: " << fragmentPath << "\t" << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //Creamos el programa shader
    *this->idProgram= glCreateProgram();
    glAttachShader(*this->idProgram,Vertex);
    glAttachShader(*this->idProgram,fragment);
    glLinkProgram(*this->idProgram);
    glGetProgramiv(*this->idProgram,GL_LINK_STATUS,&success);
    if (!success){
        glGetProgramInfoLog(*this->idProgram,512,nullptr,infoLog);
        cout << "hgsShader Error al realizar el link del programa:\n" << infoLog << endl;
    }

    //Borramos los shaders
    glDeleteShader(Vertex);
    glDeleteShader(fragment);

}


ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath)
: idProgram(new unsigned(0),deleteShaderProgram){

    //Abrimos los ficheros y los convertimos en char*.
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    ifstream fileVertex;
    ifstream fileFragment;
    ifstream fileGeometry;
    fileVertex.exceptions(ifstream::failbit | ifstream::badbit);
    fileFragment.exceptions(ifstream::failbit | ifstream::badbit);
    fileGeometry.exceptions(ifstream::failbit | ifstream::badbit);
    try{
        fileVertex.open(vertexPath);
        fileFragment.open(fragmentPath);
        fileGeometry.open(geometryPath);

        stringstream vStream,fStream,gStream;
        vStream << fileVertex.rdbuf();
        fStream << fileFragment.rdbuf();
        gStream << fileGeometry.rdbuf();

        vertexCode= vStream.str();
        fragmentCode= fStream.str();
        geometryCode= gStream.str();
    }catch(ifstream::failure e){
        cout << "hgsShader Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    const char* vCode= vertexCode.c_str();
    const char* fCode= fragmentCode.c_str();
    const char* gCode= geometryCode.c_str();

    //Compilacion
    int success;
    char infoLog[512];

    //Compilamos vertex shader
    unsigned int Vertex;

    Vertex= glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Vertex,1,&vCode,nullptr);
    glCompileShader(Vertex);
    glGetShaderiv(Vertex,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(Vertex,512,nullptr,infoLog);
        cout << "hgsShader Error al compilar vertex shader: " << vertexPath << "\n" << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //Compilamos fragment shader
    unsigned int fragment;

    fragment= glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fCode,nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(fragment,512,nullptr,infoLog);
        cout << "hgsShader Error al compilar fragment shader: " << fragmentPath << "\n" << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //Compilamos geometry shader
    unsigned int geometry;

    geometry= glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry,1,&gCode,nullptr);
    glCompileShader(geometry);
    glGetShaderiv(geometry,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(geometry,512,nullptr,infoLog);
        cout << "hgsShader Error al compilar geometry shader: " << geometryPath << "\n" << infoLog << endl;
        exit(EXIT_FAILURE);
    }

    //Creamos el programa shader
    *this->idProgram= glCreateProgram();
    glAttachShader(*this->idProgram,Vertex);
    glAttachShader(*this->idProgram,fragment);
    glAttachShader(*this->idProgram,geometry);
    glLinkProgram(*this->idProgram);
    glGetProgramiv(*this->idProgram,GL_LINK_STATUS,&success);
    if (!success){
        glGetProgramInfoLog(*this->idProgram,512,nullptr,infoLog);
        cout << "hgsShader Error al realizar el link del programa:\n" << infoLog << endl;
    }

    //Borramos los shaders
    glDeleteShader(Vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);

}


Mesh ShaderProgram::createMesh(const MeshInfo& m) const{
    return Mesh(m.MeshName,this->createVao(m.vaoInfo),m.MeshMaterial);
}

Model ShaderProgram::createModel(const std::vector<hgs::MeshInfo>& vm) const{
    std::vector<Mesh> vectorMesh;
    for (const MeshInfo& m : vm){
        vectorMesh.push_back(this->createMesh(m));
    }
    return Model(std::move(vectorMesh));
}


