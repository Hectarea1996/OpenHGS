#ifndef GAMMACORRECTION_H_INCLUDED
#define GAMMACORRECTION_H_INCLUDED

namespace hgs{

namespace GammaCorrection{

    void activar();
    void desactivar();

}

inline void GammaCorrection::activar(){
    glEnable(GL_FRAMEBUFFER_SRGB);
}

inline void GammaCorrection::desactivar(){
    glDisable(GL_FRAMEBUFFER_SRGB);
}

}


#endif // GAMMACORRECTION_H_INCLUDED
