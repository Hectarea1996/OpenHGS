
#include "OpenHGS.h"
#include "hgsVideo/Ventana.h"
#include "hgsUtil/Tiempo.h"
#include "hgsVideo/Camara.h"
#include "hgsShader/ShaderInstancing.h"
#include "hgsShader/ShaderShadow.h"
#include "hgsFrameBuffer/FaceCulling.h"
#include "hgsShader/ShaderDepth.h"
#include "hgsFigura/Rectangulo.h"
#include "hgsFigura/Cubo.h"
#include "hgsMaterial/materialFactory.h"
#include "hgsVideo/Mesh.h"
#include "hgsVideo/Model.h"
#include "hgsFrameBuffer/DepthTest.h"
#include "hgsVideo/LuzDireccion.h"
#include "hgsVideo/LuzLinterna.h"
#include "hgsFrameBuffer/FrameBuffer.h"
#include "hgsFrameBuffer/FrameBufferCubeMap.h"
#include "hgsFrameBuffer/Color.h"
#include "hgsShader/ShaderTexture.h"
#include "hgsShader/ShaderSkybox.h"
#include "hgsVideo/Skybox.h"
#include "hgsVideo/CubeMap.h"
#include "hgsUniformBuffer/UboProjection.h"
#include "hgsUniformBuffer/UboView.h"
#include "hgsUniformBuffer/UboLuzDireccion.h"
#include "hgsUniformBuffer/UboLuzPunto.h"
#include "hgsUniformBuffer/UboLuzLinterna.h"
#include "hgsUniformBuffer/UboViewPos.h"
#include "hgsFrameBuffer/MSAA.h"
#include "hgsFrameBuffer/Blending.h"
#include "hgsFrameBuffer/GammaCorrection.h"
#include "hgsShader/ShaderColor.h"
#include "hgsShader/ShaderShadowCubeMap.h"
#include "hgsShader/ShaderMap.h"


using namespace std;
using namespace glm;
using namespace hgs;



static void movimiento(vec3& posicion, float vel, const Teclado& teclado, Camara& camara){

    if (teclado.teclaPulsada(GLFW_KEY_W))
        posicion+= camara.getDelante()*vel;
    if (teclado.teclaPulsada(GLFW_KEY_S))
        posicion-= camara.getDelante()*vel;
    if (teclado.teclaPulsada(GLFW_KEY_D))
        posicion+= camara.getDerecha()*vel;
    if (teclado.teclaPulsada(GLFW_KEY_A))
        posicion-= camara.getDerecha()*vel;
    if (teclado.teclaPulsada(GLFW_KEY_SPACE))
        posicion+= vec3(0,1,0)*vel;
    if (teclado.teclaPulsada(GLFW_KEY_LEFT_CONTROL))
        posicion-= vec3(0,1,0)*vel;

}


int main(){

    hgs::iniciar();

    Ventana ventana("Prueba",1366,768,false,4);

    Loader load;
    load.LoadFile("./Modelos/LowPolyTree/LowPolyTree.obj");

    Tiempo tiempo;
    Camara camara(1366,768);
    Camara luzDirCamara(1024,1024); //Utilizando valores grandes (>2000) puede petar.
    luzDirCamara.projection.setOrthogonal(-10.0f,10.0f,-10.0f,10.0f,0.1f,30.0f);
    Camara luzPunCamara(1024,1024);
    luzPunCamara.projection.setPerspective(1024,1024,radians(90.0),0.1,100);
    Teclado& teclado= ventana.teclado;
    Raton& raton= ventana.raton;

    ShaderColor shaderColor;
    //ShaderTexture shaderTexture;
    ShaderSkybox shaderSkybox;
    ShaderShadow shaderShadow;
    ShaderShadowCubeMap shaderShadowCubeMap;
    ShaderMap shaderMap;

    FrameBuffer<HGS_RENDERBUFFER_DEPTH> frameBufferDepth(1024,1024);
    FrameBufferCubeMap<HGS_RENDERBUFFER_DEPTH> frameBufferDepthCube(1024);

    DepthTest::activar();
    raton.setMode(HGS_CURSOR_DESACTIVADO);



    //Inicializar Shaders.
    shaderColor.usar();
    shaderColor.setSkybox(CubeMap(HGS_EXAMPLE_DESERT));

    shaderSkybox.usar();
    Skybox skybox(CubeMap(HGS_EXAMPLE_DOWNUNDER),shaderSkybox.createVao(Skybox::getVaoInfo()));
    shaderSkybox.setCubeMap(skybox.cubeMap);

    shaderShadow.usar();
    shaderShadow.setProjectionMatrix(luzDirCamara.projection);

    shaderShadowCubeMap.usar();
    shaderShadowCubeMap.setProjectionMatrix(luzPunCamara.projection);


    //Inicializar UBO.
    UboProjection& uboProjection= UboProjection::getInstancia();
    uboProjection.setProjectionMatrix(camara.projection.getProjectionMatrix());

    UboView& uboView= UboView::getInstancia();
    UboViewPos& uboViewPos= UboViewPos::getInstancia();

//    UboLuzPunto& uboPun= UboLuzPunto::getInstancia();
//    LuzPunto luzPun(vec3(-2,0,0),vec3(1,1,1),vec3(1,1,1),vec3(1,1,1),Atenuacion(1,0.5,0.6));
//    uboPun.setLuzPunto(luzPun,0);
    UboLuzDireccion& uboDir= UboLuzDireccion::getInstancia();
    LuzDireccion luzDir(vec3(0.5,-1,4),vec3(1,1,1),vec3(1,1,1),vec3(1,1,1));
    uboDir.setLuzDireccion(luzDir,0);



    //Inicializar modelos.
    Model cubo(shaderColor.createModel(load.LoadedMeshes));
//    Model cubo(shaderColor.createMesh(MeshInfo(Cubo::getVaoInfo())));
    cubo.modelMatrix.setScale(vec3(0.1,0.1,0.1));
    for (Mesh& mesh: cubo.meshVector){
        mesh.meshMaterial.Ka.r= 108*0.2*0.004;
        mesh.meshMaterial.Ka.g= 59*0.2*0.004;
        mesh.meshMaterial.Ka.b= 49*0.2*0.004;
        mesh.meshMaterial.Kd.r=108.0*0.004;
        mesh.meshMaterial.Kd.g=59.0*0.004;
        mesh.meshMaterial.Kd.b=49.0*0.004;
        mesh.meshMaterial.Ks.r=0.5;
        mesh.meshMaterial.Ks.g=0.5;
        mesh.meshMaterial.Ks.b=0.5;
    }

    Model suelo(shaderColor.createMesh(MeshInfo(Cubo::getVaoInfo())));
    suelo.modelMatrix.setScale(vec3(10,10,1));
    suelo.modelMatrix.setEulerAngles(0,radians(90.0),0);
    suelo.modelMatrix.setPosition(vec3(0,-1.1,0));
    Mesh& meshSuelo= suelo.meshVector[0];
    meshSuelo.meshMaterial.Ka= vec3(0.1,0.1,0.1);
    meshSuelo.meshMaterial.Kd= vec3(0.2,0.2,0.2);
    meshSuelo.meshMaterial.Ks= vec3(0.2,0.2,0.2);

    Model pared(shaderColor.createMesh(MeshInfo(Cubo::getVaoInfo())));
    pared.modelMatrix.setScale(vec3(10,10,1));
    pared.modelMatrix.setEulerAngles(radians(90.0),0,0);
    pared.modelMatrix.setPosition(vec3(-8,0,0));
    Mesh& meshPared= pared.meshVector[0];
    meshPared.meshMaterial.Ka= vec3(0.1,0.1,0.1);
    meshPared.meshMaterial.Kd= vec3(0.2,0.2,0.2);
    meshPared.meshMaterial.Ks= vec3(0.2,0.2,0.2);


    //---
    Model cuboShadow(shaderShadow.createModel(load.LoadedMeshes));
    cuboShadow.modelMatrix.setScale(vec3(0.1,0.1,0.1));

    Model sueloShadow(shaderShadow.createMesh(MeshInfo(Cubo::getVaoInfo())));
    sueloShadow.modelMatrix.setScale(vec3(10,10,1));
    sueloShadow.modelMatrix.setEulerAngles(0,radians(90.0),0);
    sueloShadow.modelMatrix.setPosition(vec3(0,-1.1,0));

    Model paredShadow(shaderShadow.createMesh(MeshInfo(Cubo::getVaoInfo())));
    paredShadow.modelMatrix.setScale(vec3(10,10,1));
    paredShadow.modelMatrix.setEulerAngles(radians(90.0),0,0);
    paredShadow.modelMatrix.setPosition(vec3(-8,0,0));

    //---
    Model quad(shaderMap.createMesh(MeshInfo(Rectangulo::getVaoInfo())));
    quad.modelMatrix.setScale(vec3(0.2,0.3,1.0));
    quad.modelMatrix.setPosition(vec3(0.75,0.6,0.0));




    //Inicializar raton y teclado
    //float offset= 0;

    float yaw= 0;
    float pitch= 0;
    float roll= 0;
    float velCursor= 70;

    function<void(double cantX, double cantY)> angulos= [&yaw,&pitch,velCursor,&tiempo](double cantX, double cantY){
        yaw-= cantX*velCursor*tiempo.cogerFactorLambda()*1.5;
        pitch-= cantY*velCursor*tiempo.cogerFactorLambda();
    };
    raton.insertarMovListener(&angulos);

//    function<void(int key, int scancode, int action, int mods)> tab= [&skybox](int key, int scancode, int action, int mods){
//        static int example= HGS_EXAMPLE_DOWNUNDER;
//        if (key==GLFW_KEY_TAB && action==GLFW_PRESS){
//            skybox.cubeMap= CubeMap((++example)%3);
//        }
//    };
//    teclado.insertarListener(&tab);

    function<void(int key, int scancode, int action, int mods)> pressX= [](int key, int scancode, int action, int mods){
        static bool activado= true;
        if (key==GLFW_KEY_X && action==GLFW_PRESS){
            if (activado)
                MSAA::desactivar();
            else
                MSAA::activar();
            activado= !activado;
        }
    };
    teclado.insertarListener(&pressX);

    function<void(int key, int scancode, int action, int mods)> pressG= [](int key, int scancode, int action, int mods){
        static bool activado= true;
        if (key==GLFW_KEY_G && action==GLFW_PRESS){
            if (activado)
                GammaCorrection::desactivar();
            else
                GammaCorrection::activar();
            activado= !activado;
        }
    };
    teclado.insertarListener(&pressG);

    //Variables globales.
    vec3 posicion(0,0.1,7);

    while (!ventana.deberiaCerrarse()){

        cout << "Inicio: " << glGetError() << "\t";

        tiempo.controlarFactorLambda();
        ventana.actualizarEventos();

        if (teclado.teclaPulsada(GLFW_KEY_ESCAPE)){
            ventana.debeCerrarse();
        }

        float vel= 5*tiempo.cogerFactorLambda();
        movimiento(posicion,vel,teclado,camara);
        camara.setPosicion(posicion);
        camara.setEulerAngles(radians(yaw),radians(pitch),radians(roll));

        luzDirCamara.lookAt(posicion-luzDir.direccion*2.0f,posicion);


        uboView.setViewMatrix(camara.view.getViewMatrix());
        uboViewPos.setViewPosition(camara.view.getPosition());

        shaderShadow.usar();
        shaderShadow.setViewMatrix(luzDirCamara.view);

        shaderShadowCubeMap.usar();
        shaderShadowCubeMap.setLightPosition(luzPun.position);

//        offset+= tiempo.cogerFactorLambda()*0.001;
//        static float numModels= 100;
//        int velCambio= 100;
//        if (numModels<10)
//            numModels= 10;
//
//        if (teclado.teclaPulsada(GLFW_KEY_UP))
//            numModels+= tiempo.cogerFactorLambda()*velCambio;
//        if (teclado.teclaPulsada(GLFW_KEY_DOWN))
//            numModels-= tiempo.cogerFactorLambda()*velCambio;


        //Sombras direccion
        {
            frameBufferDepth.usar();
            Color::setColor(0,0,0,1.0);
            Color::limpiar();
            DepthTest::limpiar();

            FaceCulling::activar();

            //Suelo
            shaderShadow.usar();
            shaderShadow.setModelMatrix(sueloShadow.modelMatrix);
            sueloShadow.dibuja(GL_TRIANGLES);

            //Pared
            shaderShadow.usar();
            shaderShadow.setModelMatrix(paredShadow.modelMatrix);
            paredShadow.dibuja(GL_TRIANGLES);

            //Cubo
            shaderShadow.usar();
            shaderShadow.setModelMatrix(cuboShadow.modelMatrix);
            cuboShadow.dibuja(GL_TRIANGLES);

            FaceCulling::desactivar();

        }

        {

            ventana.usarFramebuffer();

            Color::setColor(0.1,0.1,0.1,1.0);
            Color::limpiar();
            DepthTest::limpiar();

            shaderColor.usar();
            shaderColor.setShadowDirMap(frameBufferDepth.getRenderTexture());
            shaderColor.setLightDirSpaceMatrix(luzDirCamara.projection.getProjectionMatrix()*luzDirCamara.view.getViewMatrix());
            //shaderColor.setLightPoint_farPlane(camara.projection.getFar());

            //Suelo
            shaderColor.usar();
            shaderColor.setModelMatrix(suelo.modelMatrix);
            shaderColor.setMaterial(suelo.meshVector[0].meshMaterial);
            suelo.dibuja(GL_TRIANGLES);


            //Pared
            shaderColor.usar();
            shaderColor.setModelMatrix(pared.modelMatrix);
            shaderColor.setMaterial(pared.meshVector[0].meshMaterial);
            pared.dibuja(GL_TRIANGLES);

            //Cubo
            shaderColor.usar();
            shaderColor.setModelMatrix(cubo.modelMatrix);
            shaderColor.setMaterial(cubo.meshVector[0].meshMaterial);
            cubo.dibuja(GL_TRIANGLES);


            //Skybox
            shaderSkybox.usar();
            shaderSkybox.setCubeMap(skybox.cubeMap);
            DepthTest::setFuncion(HGS_FUNCDEPTH_LEQUAL);
            skybox.vao.dibuja(GL_TRIANGLES);
            DepthTest::setFuncion(HGS_FUNCDEPTH_LESS);
        }

        {
            ventana.usarFramebuffer();

            DepthTest::limpiar();

            shaderMap.usar();
            shaderMap.setMap(frameBufferDepth.getRenderTexture());
            shaderMap.setModelMatrix(quad.modelMatrix);
            quad.dibuja(GL_TRIANGLES);

        }


        ventana.actualizar();

    }

    return 0;

}
