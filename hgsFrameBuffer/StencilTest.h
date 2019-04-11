#ifndef STENCILTEST_H_INCLUDED
#define STENCILTEST_H_INCLUDED

#define HGS_FUNCSTENCIL_ALWAYS      GL_ALWAYS
#define HGS_FUNCSTENCIL_NEVER       GL_NEVER
#define HGS_FUNCSTENCIL_EQUAL       GL_EQUAL
#define HGS_FUNCSTENCIL_NOTEQUAL    GL_NOTEQUAL
#define HGS_FUNCSTENCIL_LESS        GL_LESS
#define HGS_FUNCSTENCIL_GREATER     GL_GREATER
#define HGS_FUNCSTENCIL_LEQUAL      GL_LEQUAL
#define HGS_FUNCSTENCIL_GEQUAL      GL_GEQUAL

#define HGS_OPSTENCIL_KEEP          GL_KEEP
#define HGS_OPSTENCIL_ZERO          GL_ZERO
#define HGS_OPSTENCIL_REPLACE       GL_REPLACE
#define HGS_OPSTENCIL_INCR          GL_INCR
#define HGS_OPSTENCIL_INCR_WRAP     GL_INCR_WRAP
#define HGS_OPSTENCIL_DECR          GL_DECR
#define HGS_OPSTENCIL_DECR_WRAP     GL_DECR_WRAP
#define HGS_OPSTENCIL_INVERT        GL_INVERT


namespace hgs{

namespace StencilTest{

    void activar();
    void desactivar();
    void setMascara(unsigned int mascara);
    void setFuncion(unsigned int HGS_FUNCSTENCIL, unsigned int valueComp, unsigned int mascara);
    void setOperacion(unsigned int HGS_OPSTENCIL_sfail, unsigned int HGS_OPSTENCIL_dpfail, unsigned int HGS_OPSTENCIL_dppass);
    void setStencil(unsigned int s);
    void limpiar();

};

inline void StencilTest::activar(){
    glEnable(GL_STENCIL_TEST);
}

inline void StencilTest::desactivar(){
    glDisable(GL_STENCIL_TEST);
}

inline void StencilTest::setMascara(unsigned int mascara){
    glStencilMask(mascara);
}

inline void StencilTest::setFuncion(unsigned int HGS_FUNCSTENCIL, unsigned int valueComp, unsigned int mascara){
    glStencilFunc(HGS_FUNCSTENCIL,valueComp,mascara);
}

inline void StencilTest::setOperacion(unsigned int HGS_OP_sfail, unsigned int HGS_OP_dpfail, unsigned int HGS_OP_dppass){
    glStencilOp(HGS_OPSTENCIL_sfail,HGS_OPSTENCIL_dpfail,HGS_OPSTENCIL_dppass);
}

inline void StencilTest::setStencil(unsigned int s){
    glClearStencil(s);
}

inline void StencilTest::limpiar(){
    glClear(GL_STENCIL_BUFFER_BIT);
}


}

#endif // STENCILTEST_H_INCLUDED
