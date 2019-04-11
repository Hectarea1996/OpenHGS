#ifndef FRAMEBUFFERCUBEMAP_H_INCLUDED
#define FRAMEBUFFERCUBEMAP_H_INCLUDED

#include "../OpenHGS.h"
#include "../hgsVideo/CubeMap.h"
#include "../hgsTemplate/enable_function.h"

#ifndef HGS_RENDERBUFFER_NONE
    #define HGS_RENDERBUFFER_NONE           0
    #define HGS_RENDERBUFFER_DEPTH          1
    #define HGS_RENDERBUFFER_STENCIL        2
    #define HGS_RENDERBUFFER_DEPTH_STENCIL  3
#endif // HGS_RENDERBUFFER_NONE

namespace hgs{

template<unsigned int R>
class FrameBufferCubeMap{

    template<unsigned int U>
    friend class FrameBufferCubeMap;

    private:

        std::shared_ptr<unsigned> FBO;
        CubeMap renderCubeMap;
        unsigned int lado;


    public:

        FrameBufferCubeMap(unsigned int lado);

        template<unsigned int U>
        void blitFrameBufferCubeMap(const FrameBufferCubeMap<U>& dst);

        void usar() const;

        CubeMap getRenderCubeMap() const;
        unsigned int getFBO();

};

template<unsigned int R>
struct getVarRenderCube{
    static const unsigned int internalformat= 0;
    static const unsigned int attachment= 0;
};

template<>
struct getVarRenderCube<HGS_RENDERBUFFER_DEPTH>{
    static const unsigned int internalformat= GL_DEPTH_COMPONENT;
    static const unsigned int attachment= GL_DEPTH_ATTACHMENT;
};

template<>
struct getVarRenderCube<HGS_RENDERBUFFER_STENCIL>{
    static const unsigned int internalformat= GL_STENCIL_INDEX;
    static const unsigned int attachment= GL_STENCIL_ATTACHMENT;
};

template<>
struct getVarRenderCube<HGS_RENDERBUFFER_DEPTH_STENCIL>{
    static const unsigned int internalformat= GL_DEPTH24_STENCIL8;
    static const unsigned int attachment= GL_DEPTH_STENCIL_ATTACHMENT;
};

template<unsigned int R>
static void generarRenderBufferCube(unsigned int lado){
    unsigned int rbo;
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,getVarRenderCube<R>::internalformat,lado,lado);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,getVarRenderCube<R>::attachment,GL_RENDERBUFFER,rbo);
}

template<unsigned int R>
FrameBufferCubeMap<R>::FrameBufferCubeMap(unsigned int lado)
: FBO(new unsigned(0)), lado(lado){

    unsigned int textureId= this->renderCubeMap.getCubeMapId();

    glGenFramebuffers(1,this->FBO.get());
    unsigned int fbo= *this->FBO;
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->lado, this->lado, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP,0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X,textureId,0);

    enable_function_if<R!=HGS_RENDERBUFFER_NONE,void>::ejecutar(generarRenderBufferCube<R>,lado);

    unsigned int status= glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status!=GL_FRAMEBUFFER_COMPLETE){
        std::cout << "FrameBufferCubeMap no esta completo: ";
        switch (status){
            case GL_FRAMEBUFFER_UNDEFINED :
                cout << "GL_FRAMEBUFFER_UNDEFINED " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER  :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER  " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE  :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE  " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  " << endl;
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
                break;
        }

        exit(EXIT_FAILURE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);

}


template<unsigned int R>
template<unsigned int S>
inline void FrameBufferCubeMap<R>::blitFrameBufferCubeMap(const FrameBufferCubeMap<S>& dst){
    glBindFramebuffer(GL_READ_FRAMEBUFFER,*this->FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,*dst.FBO);
    glBlitFramebuffer(0,0,this->ancho,this->alto,
                      0,0,dst.ancho,dst.alto,
                      GL_COLOR_BUFFER_BIT,GL_NEAREST);
}

template<unsigned int R>
inline void FrameBufferCubeMap<R>::usar() const{
    glViewport(0,0,this->lado,this->lado);
    glBindFramebuffer(GL_FRAMEBUFFER,*this->FBO);
}


template<unsigned int R>
inline CubeMap FrameBufferCubeMap<R>::getRenderCubeMap() const{
    return this->renderCubeMap;
}

template<unsigned int R>
inline unsigned int FrameBufferCubeMap<R>::getFBO(){
    return *this->FBO;
}

}


#endif // FRAMEBUFFERCUBEMAP_H_INCLUDED
