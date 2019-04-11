#ifndef FACECULLING_H_INCLUDED
#define FACECULLING_H_INCLUDED

#define HGS_CULLFACE_FRONT              GL_FRONT
#define HGS_CULLFACE_BACK               GL_BACK
#define HGS_CULLFACE_FRONT_AND_BACK     GL_FRONT_AND_BACK

#define HGS_CULLORI_CCW                 GL_CCW
#define HGS_CULLORI_CW                  GL_CW


namespace hgs{

namespace FaceCulling{

    void activar();
    void desactivar();
    void cullFace(unsigned int HGS_CULLFACE);
    void frontFace(unsigned int HGS_CULLORI);

};


inline void FaceCulling::activar(){
    glEnable(GL_CULL_FACE);
}

inline void FaceCulling::desactivar(){
    glDisable(GL_CULL_FACE);
}

inline void FaceCulling::cullFace(unsigned int HGS_CULLFACE){
    glCullFace(HGS_CULLFACE);
}

inline void FaceCulling::frontFace(unsigned int HGS_CULLORI){
    glFrontFace(HGS_CULLORI);
}


}

#endif // FACECULLING_H_INCLUDED
