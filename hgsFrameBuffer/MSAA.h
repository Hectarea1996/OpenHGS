#ifndef MSAA_H_INCLUDED
#define MSAA_H_INCLUDED

namespace hgs{

namespace MSAA{

    void activar();
    void desactivar();
    //void blitFrameBuffers(const FrameBuffer& src, const FrameBuffer& dst);

}

inline void MSAA::activar(){
    glEnable(GL_MULTISAMPLE);
}

inline void MSAA::desactivar(){
    glDisable(GL_MULTISAMPLE);
}

}

#endif // MSAA_H_INCLUDED
