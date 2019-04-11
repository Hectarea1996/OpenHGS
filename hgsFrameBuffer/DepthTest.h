#ifndef DEPTHTEST_H_INCLUDED
#define DEPTHTEST_H_INCLUDED

#define HGS_FUNCDEPTH_ALWAYS    GL_ALWAYS
#define HGS_FUNCDEPTH_NEVER     GL_NEVER
#define HGS_FUNCDEPTH_EQUAL     GL_EQUAL
#define HGS_FUNCDEPTH_NOTEQUAL  GL_NOTEQUAL
#define HGS_FUNCDEPTH_LESS      GL_LESS
#define HGS_FUNCDEPTH_GREATER   GL_GREATER
#define HGS_FUNCDEPTH_LEQUAL    GL_LEQUAL
#define HGS_FUNCDEPTH_GEQUAL    GL_GEQUAL

namespace hgs{

namespace DepthTest{

    void activar();
    void desactivar();
    void setMascara(bool flag);
    void setFuncion(unsigned int HGS_FUNCDEPTH= HGS_FUNCDEPTH_LESS);
    void setDepth(double depth);
    void limpiar();

};


inline void DepthTest::activar(){
    glEnable(GL_DEPTH_TEST);
}

inline void DepthTest::desactivar(){
    glDisable(GL_DEPTH_TEST);
}

inline void DepthTest::setMascara(bool flag){
    glDepthMask(flag);
}

inline void DepthTest::setFuncion(unsigned int func){
    glDepthFunc(func);
}

inline void DepthTest::setDepth(double depth){
    glClearDepth(depth);
}

inline void DepthTest::limpiar(){
    glClear(GL_DEPTH_BUFFER_BIT);
}

}

#endif // DEPTHTEST_H_INCLUDED
