#ifndef SUPERSPACE_H_INCLUDED
#define SUPERSPACE_H_INCLUDED

class SuperSpace{

    private:

        std::array<Model,6> cuartos;
        Model pared1;
        Model pared2;


    public:

        SuperSpace(std::array<Model,6> cuartos);
        void dibuja();


};

SuperSpace::SuperSpace(std::array<Model,6> cuartos): cuartos(cuartos), pared1(){}

void SuperSpace::dibuja(){

    //Parte principal
    for (int i=2; i<=3; i++){
        for (Mesh& mesh : cuartos[i]){
            std::weak_ptr<ShaderProgram> shaderProgram(mesh.getShaderProgram());
            shaderProgram->setMaterial(mesh.meshMaterial);
            mesh.dibuja();
        }
    }

    //ParteIzquierda
    stencilTest::activar();



}


#endif // SUPERSPACE_H_INCLUDED
